#include "BTTask_Spin.h"

#include "AIController.h"

UBTTask_Spin::UBTTask_Spin()
{
	NodeName = TEXT("Spin");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Spin::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Rotation = 0.f;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Spin::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	
	const auto AIOwner = OwnerComp.GetAIOwner();
	const auto Pawn = AIOwner->GetPawn();
	
	const float DeltaRotation = DeltaSeconds * SpinSpeed;
	Rotation += DeltaRotation;
	
	Pawn->AddActorLocalRotation(FRotator(0.f, DeltaRotation, 0.f));
	
	if (Rotation >= 360.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
