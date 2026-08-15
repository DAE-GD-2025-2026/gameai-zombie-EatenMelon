#include "BTDecorator_IsInRange.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInRange::UBTDecorator_IsInRange()
{
	NodeName = TEXT("Is In Range");
}

bool UBTDecorator_IsInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();

	if (AIOwner == nullptr)
	{
		return false;
	}

	const APawn* Pawn = AIOwner->GetPawn();
	
	if (Pawn == nullptr)
	{
		return false;
	}

	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();

	if (BlackboardComponent == nullptr)
	{
		return false;
	}

	const AActor* TargetActor = Cast<AActor>(BlackboardComponent->GetValueAsObject(Target.SelectedKeyName));

	if (TargetActor == nullptr)
	{
		return false;
	}
	
	FVector StartLocation = Pawn->GetActorLocation();
	FVector TargetLocation = TargetActor->GetActorLocation();
	
	FHitResult HitResult{};

	FCollisionQueryParams QueryParams{};
	QueryParams.AddIgnoredActor(Pawn);
	QueryParams.AddIgnoredActor(TargetActor);

	const bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		TargetLocation,
		ECC_Visibility,
		QueryParams
	);

	if (Hit)
	{
		return false;
	}

	StartLocation.Z = 0.f;
	TargetLocation.Z = 0.f;
	
	return FVector::DistSquared(StartLocation, TargetLocation) <= Distance * Distance;
}
