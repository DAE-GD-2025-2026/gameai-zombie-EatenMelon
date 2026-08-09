#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Spin.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_Spin : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Spin();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	virtual void TickTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory,
		float DeltaSeconds
	) override;

private:
	float Rotation{ 0.f };

	UPROPERTY(EditAnywhere, Category = "Spin")
	float SpinSpeed{ 500.0f };
};
