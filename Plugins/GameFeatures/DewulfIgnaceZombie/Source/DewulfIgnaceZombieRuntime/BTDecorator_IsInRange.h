#pragma once
#include "BehaviorTree/BTDecorator.h"

#include "BTDecorator_IsInRange.generated.h"

UCLASS()
class UBTDecorator_IsInRange final : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_IsInRange();
	
	UPROPERTY(EditAnywhere, Category = "Distance")
	float Distance = 100.f;

	UPROPERTY(EditAnywhere, Category = "Distance")
	FBlackboardKeySelector Target;
	
protected:
	virtual bool CalculateRawConditionValue
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) const override;
};
