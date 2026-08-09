#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Evade.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_Evade : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Evade();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	FBlackboardKeySelector TargetType;
};
