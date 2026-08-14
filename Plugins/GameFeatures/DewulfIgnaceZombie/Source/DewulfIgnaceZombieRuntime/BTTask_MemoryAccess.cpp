#include "BTTask_MemoryAccess.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UStudentMemory* UBTTask_MemoryAccess::GetStudentMemory(const UBehaviorTreeComponent& OwnerComp)
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
		
	if (AIOwner == nullptr) return nullptr;
		
	const APawn* Pawn = AIOwner->GetPawn();
		
	if (Pawn == nullptr) return nullptr;
	
	UStudentMemory* StudentMemory = Cast<UStudentMemory>
		(
			Pawn->FindComponentByClass(UStudentMemory::StaticClass())
		);

	return StudentMemory;
}

UBTTask_Forget::UBTTask_Forget()
{
	NodeName = TEXT("Forget");
}

EBTNodeResult::Type UBTTask_Forget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UStudentMemory* StudentMemory = GetStudentMemory(OwnerComp);
	
	if (StudentMemory == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AActor* TargetActor = 
		Cast<AActor>(BlackboardComponent->GetValueAsObject(Target.SelectedKeyName));
	
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	StudentMemory->Forget(TargetActor);
	
	return EBTNodeResult::Succeeded;
}

UBTTask_GetClosestHouse::UBTTask_GetClosestHouse()
{
	NodeName = TEXT("Get Closest House");
}

EBTNodeResult::Type UBTTask_GetClosestHouse::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UStudentMemory* StudentMemory = GetStudentMemory(OwnerComp);
	
	if (StudentMemory == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	auto Houses = StudentMemory->GetHouses();
	if (Houses.empty())
	{
		return EBTNodeResult::Failed;
	}
	
	const FVector Start = StudentMemory->GetOwner()->GetActorLocation();
	std::ranges::sort
	(
		Houses,
		[&](const AHouse* A, const AHouse* B)
		{
			const auto ToA = FVector::DistSquared(Start, A->GetActorLocation());
			const auto ToB = FVector::DistSquared(Start, B->GetActorLocation());
			
			return ToA < ToB;
		}
	);
	
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	
	if (BlackBoard == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackBoard->SetValueAsObject
	(
		Target.SelectedKeyName,
		Houses.front()
	);
	
	return EBTNodeResult::Succeeded;
}

UBTTask_GetClosestItem::UBTTask_GetClosestItem()
{
	NodeName = TEXT("Get Closest Item");
}

EBTNodeResult::Type UBTTask_GetClosestItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UStudentMemory* StudentMemory = GetStudentMemory(OwnerComp);
	
	if (StudentMemory == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	auto Items = StudentMemory->GetItems();
	if (Items.empty())
	{
		return EBTNodeResult::Failed;
	}
	
	const FVector Start = StudentMemory->GetOwner()->GetActorLocation();
	std::ranges::sort
	(
		Items,
		[&](const ABaseItem* A, const ABaseItem* B)
		{
			const auto ToA = FVector::DistSquared(Start, A->GetActorLocation());
			const auto ToB = FVector::DistSquared(Start, B->GetActorLocation());
			
			return ToA < ToB;
		}
	);
	
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	
	if (BlackBoard == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackBoard->SetValueAsObject
	(
		Target.SelectedKeyName,
		Items.front()
	);
	
	return EBTNodeResult::Succeeded;
}

UBTTask_GetClosestZombie::UBTTask_GetClosestZombie()
{
	NodeName = TEXT("Get Closest Zombie");
}

EBTNodeResult::Type UBTTask_GetClosestZombie::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UStudentMemory* StudentMemory = GetStudentMemory(OwnerComp);
	
	if (StudentMemory == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	std::vector<ABaseZombie*> Zombies = StudentMemory->GetZombies();
	
	if (Zombies.empty())
	{
		return EBTNodeResult::Failed;
	}
	
	const FVector Start = StudentMemory->GetOwner()->GetActorLocation();
	
	std::ranges::sort
	(
		Zombies,
		[&](const ABaseZombie* A, const ABaseZombie* B)
		{
			const auto ToA = FVector::DistSquared(Start, A->GetActorLocation());
			const auto ToB = FVector::DistSquared(Start, B->GetActorLocation());
			
			return ToA < ToB;
		}
	);
	
	UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
	
	if (BlackBoard == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackBoard->SetValueAsObject
	(
		Target.SelectedKeyName,
		Zombies.front()
	);
	
	return EBTNodeResult::Succeeded;
}
