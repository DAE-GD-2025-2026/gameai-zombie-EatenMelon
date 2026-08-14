#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayerInfoAccess.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetHealthPercentage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetHealthPercentage();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FBlackboardKeySelector HealthPercent;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetStaminaPercentage : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetStaminaPercentage();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FBlackboardKeySelector StaminaPercent;
};
