#include "BTTask_MemoryAccess.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UStudentMemory* UBTTask_MemoryAccess::GetStudentMemory(UBehaviorTreeComponent& OwnerComp)
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

UBTTask_GetClosestHouse::UBTTask_GetClosestHouse()
{
	NodeName = TEXT("GetClosestHouse");
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
		Output.SelectedKeyName,
		Houses.front()
	);
	
	return EBTNodeResult::Succeeded;
}
