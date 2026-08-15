#include "BTTask_Face.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_Face::UBTTask_Face()
{
	NodeName = TEXT("Face");
	bNotifyTick = true;
}

EBTNodeResult::Type UBTTask_Face::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(Target.SelectedKeyName));
	
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
	
	if (AIOwner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	Pawn = AIOwner->GetPawn();
	
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AngularVelocity = 0.f;
	
	return EBTNodeResult::InProgress;
}

void UBTTask_Face::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FVector ToTarget = TargetActor->GetActorLocation() - Pawn->GetActorLocation();

	ToTarget.Z = 0.f;

	if (ToTarget.IsNearlyZero())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	const float CurrentYaw = Pawn->GetActorRotation().Yaw;
	const float TargetYaw = ToTarget.Rotation().Yaw;

	const float Diff = FMath::FindDeltaAngleDegrees(CurrentYaw, TargetYaw);

	if (FMath::Abs(Diff) < 1.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		return;
	}

	const float MaxDeltaYaw = MaxAngularVelocity * DeltaSeconds;

	const float DeltaYaw = FMath::Clamp( Diff, -MaxDeltaYaw, MaxDeltaYaw);

	Pawn->SetActorRotation(FRotator(0.f, CurrentYaw + DeltaYaw, 0.f));
}
