#include "StudentMemory.h"
#include "Survivor/SurvivorPawn.h"

UStudentMemory::UStudentMemory()
{
	
}

void UStudentMemory::TickComponent(float DeltaTime, enum ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (TimeUntilPathUpdate <= 0.f)
	{
		UpdatePaths();
	}
	else
	{
		TimeUntilPathUpdate -= DeltaTime;
	}
}

void UStudentMemory::Memorize(ABaseZombie* Zombie)
{
	const auto OwnerPos = GetOwner()->GetActorLocation();
	Zombie->OnDestroyed.AddDynamic(this, &UStudentMemory::Forget);
	
	erase_if
	(
		Zombies, 
		[&](const ABaseZombie* Z)
		{
			auto ZombiePos = Z->GetActorLocation();
			auto Dist2 = FVector::DistSquared(OwnerPos, ZombiePos);
			
			return Dist2 <= MemoryRange * MemoryRange;
		}
	);
	
	if (std::ranges::find(Zombies, Zombie) != Zombies.end()) return;
	
	Zombies.emplace_back(Zombie);
}

void UStudentMemory::Memorize(APurgeZone* PurgeZone)
{
	PurgeZone->OnDestroyed.AddDynamic(this, &UStudentMemory::Forget);
	
	if (std::ranges::find(PurgeZones, PurgeZone) != PurgeZones.end()) return;
	
	PurgeZones.emplace_back(PurgeZone);
}

void UStudentMemory::Memorize(AHouse* House)
{
	House->OnDestroyed.AddDynamic(this, &UStudentMemory::Forget);
	
	if (std::ranges::find(Houses, House) != Houses.end()) return;
	
	Houses.emplace_back(House);
}

void UStudentMemory::Memorize(ABaseItem* Item)
{
	Item->OnDestroyed.AddDynamic(this, &UStudentMemory::Forget);
	
	if (std::ranges::find(Items, Item) != Items.end()) return;
	
	Items.emplace_back(Item);
}

void UStudentMemory::Forget(const ABaseZombie* Zombie)
{
	std::erase(Zombies, Zombie);
}

void UStudentMemory::Forget(const APurgeZone* PurgeZone)
{
	std::erase(PurgeZones, PurgeZone);
}

void UStudentMemory::Forget(const AHouse* House)
{
	std::erase(Houses, House);
}

void UStudentMemory::Forget(const ABaseItem* Item)
{
	std::erase(Items, Item);
}

const TArray<FVector>& UStudentMemory::GetPathToClosestHouse() const
{
	return PathToClosestHouse;
}

void UStudentMemory::Forget(AActor* Actor)
{
	if (const auto Zombie = Cast<ABaseZombie>(Actor))
	{
		Forget(Zombie);
	}
	else if (const auto PurgeZone = Cast<APurgeZone>(Actor))
	{
		Forget(PurgeZone);
	}
	else if (const auto Item = Cast<ABaseItem>(Actor))
	{
		Forget(Item);
	}
	else if (const auto House = Cast<AHouse>(Actor))
	{
		Forget(House);
	}
}

void UStudentMemory::UpdatePaths()
{
	TimeUntilPathUpdate = 1.f;
	
	ASurvivorPawn* SurvivorPawn = Cast<ASurvivorPawn>(GetOwner());
	
	const auto OwnerPos = GetOwner()->GetActorLocation();
	
	std::ranges::sort
	(
		Houses,
		[&](const AHouse* A, const AHouse* B)
		{
			const auto ToA = FVector::DistSquared(OwnerPos, A->GetActorLocation());
			const auto ToB = FVector::DistSquared(OwnerPos, B->GetActorLocation());
			
			return ToA < ToB;
		}
	);
	
	const auto ClosestHouse = (*Houses.begin())->GetActorLocation();
	PathToClosestHouse = SurvivorPawn->CalculatePath(ClosestHouse);
}
