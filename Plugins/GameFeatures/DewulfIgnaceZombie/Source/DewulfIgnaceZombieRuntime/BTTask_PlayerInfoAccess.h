#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PlayerInfoAccess.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetHealthPercent : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetHealthPercent();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FBlackboardKeySelector HealthPercent;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetStaminaPercent : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_GetStaminaPercent();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FBlackboardKeySelector StaminaPercent;
};
