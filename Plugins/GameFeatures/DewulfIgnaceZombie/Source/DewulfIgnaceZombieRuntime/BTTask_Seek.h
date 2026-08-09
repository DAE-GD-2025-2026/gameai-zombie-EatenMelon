#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Seek.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_Seek : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Seek();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Task")
	FBlackboardKeySelector TargetType;
};
