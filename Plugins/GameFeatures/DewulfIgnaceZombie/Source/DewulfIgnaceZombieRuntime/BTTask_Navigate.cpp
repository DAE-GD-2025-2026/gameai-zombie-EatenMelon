#include "BTTask_Navigate.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Navigate::UBTTask_Navigate()
{
	NodeName = TEXT("Navigate");
	bNotifyTick = true;
	
	
}

EBTNodeResult::Type UBTTask_Navigate::ExecuteTask
(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory
)
{
	const UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	TargetActor = Cast<AActor>(BlackBoard->GetValueAsObject(TargetKey.SelectedKeyName));
	
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	StudentMemory = nullptr;
	
	CurrentTargetNodeIndex = 0;
	TimeUntilPathUpdate = 0.f;
	Path.Reset();
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Navigate::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (StudentMemory == nullptr)
	{
		const AAIController* AIOwner = OwnerComp.GetAIOwner();
		
		if (AIOwner == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
		
		const APawn* Pawn = AIOwner->GetPawn();
		
		if (Pawn == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}

		StudentMemory = Cast<UStudentMemory>
		(
			Pawn->FindComponentByClass(UStudentMemory::StaticClass())
		);

		if (StudentMemory == nullptr)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			return;
		}
	}
	
	UpdatePath(DeltaSeconds);
	CalculateSteering(OwnerComp, DeltaSeconds);
	
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTask_Navigate::UpdatePath(float DeltaSeconds)
{
	TimeUntilPathUpdate -= DeltaSeconds;
	if (TimeUntilPathUpdate > 0.f) return;
	
	const ASurvivorPawn* SurvivorPawn = Cast<ASurvivorPawn>(StudentMemory->GetOwner());
	if (SurvivorPawn == nullptr) return;
	
	Path.Reset();
	Path = SurvivorPawn->CalculatePath(TargetActor->GetActorLocation());
	
	constexpr float PathUpdateInterval = 1.f;
	TimeUntilPathUpdate = PathUpdateInterval;
	CurrentTargetNodeIndex = 0;
}

void UBTTask_Navigate::CalculateSteering(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds)
{
	constexpr float MinDist{ 1.f };
	
	const AAIController* AIOwner = OwnerComp.GetAIOwner();		
	APawn* Pawn = AIOwner->GetPawn();
	
	FVector PawnLocation = Pawn->GetActorLocation();
	PawnLocation.Z = 0.f;
	
	FVector Destination = TargetActor->GetActorLocation();
	Destination.Z = 0.f;
	
	if (FVector::DistSquared(PawnLocation, Destination) <= MinDist * MinDist)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		StudentMemory->Forget(TargetActor);
		return;
	}
	
	// flee zombies
	float TotalZombieWeight = 0.f;
	FVector FleeZombies = FVector::ZeroVector;
	
	for (const auto& Zombie: StudentMemory->GetZombies())
	{
		FVector ZombieLocation = Zombie->GetActorLocation();
		ZombieLocation.Z = 0.f;
		
		const float Distance = FVector::Dist(ZombieLocation, PawnLocation);
		const float Weight = 1.0f / FMath::Max(Distance, MinDistanceToZombies);
		
		const FVector FleeZombie = ( PawnLocation - ZombieLocation ).GetSafeNormal();
		FleeZombies += FleeZombie * Weight;
		
		TotalZombieWeight += Weight;
	}
	
	if (TotalZombieWeight > 0.f)
	{
		FleeZombies /= TotalZombieWeight;
	}
	
	// flee purge zones
	float TotalZoneWeight = 0.f;
	FVector FleePurgeZones = FVector::ZeroVector;
	
	for (const auto& Zone: StudentMemory->GetPurgeZones())
	{
		FVector ZoneCenter = Zone->GetActorLocation();
		ZoneCenter.Z = 0.f;
		
		const float Distance = FVector::Dist(ZoneCenter, PawnLocation);
		const float Weight = 1.0f / FMath::Max(Distance, MinDistanceToPurgeZones);
		
		const FVector FleeZone = ( PawnLocation - ZoneCenter ).GetSafeNormal();
		FleePurgeZones += Weight * FleeZone;
		
		TotalZoneWeight += Weight;
	}
	
	if (TotalZoneWeight > 0.f)
	{
		FleePurgeZones /= TotalZoneWeight;
	}
	
	// seek target
	if (Path.IsEmpty())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		return;
	}
	
	FVector NodeLocation = Path[CurrentTargetNodeIndex];
	NodeLocation.Z = 0.f;
	
	if (FVector::DistSquared(PawnLocation, NodeLocation) <= MinDist * MinDist)
	{
		++CurrentTargetNodeIndex;
		
		if (CurrentTargetNodeIndex >= Path.Num())
		{
			CurrentTargetNodeIndex = Path.Num() - 1;
		}
		
		NodeLocation = Path[CurrentTargetNodeIndex];
		NodeLocation.Z = 0.f;
	}
	
	const FVector SeekTarget = (NodeLocation - PawnLocation).GetSafeNormal();
	
	// blend
	FVector Movement = FVector::ZeroVector;
	Movement += SeekTarget * SearchTargetWeight;
	Movement += FleePurgeZones * AvoidPurgeZonesWeight;
	Movement += FleeZombies * AvoidZombiesWeight;
	
	const float TotalWeight = SearchTargetWeight + AvoidPurgeZonesWeight + AvoidZombiesWeight;
	if (TotalWeight > 0.f)
	{
		Movement /= TotalWeight;
		Movement = Movement.GetSafeNormal();
	}
	
	Pawn->AddMovementInput(Movement);
	
	if (!Movement.IsNearlyZero())
	{
		const FRotator TargetRotation = Movement.Rotation();

		Pawn->SetActorRotation(
			FMath::RInterpTo(
				Pawn->GetActorRotation(),
				TargetRotation,
				DeltaSeconds,
				10.f
			)
		);
	}
}
