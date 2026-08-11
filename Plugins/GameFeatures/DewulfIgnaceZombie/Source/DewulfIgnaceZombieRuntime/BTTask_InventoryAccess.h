#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "Common/InventoryComponent.h"
#include "BTTask_InventoryAccess.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_InventoryAccess: public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	static UInventoryComponent* GetInventory(const UBehaviorTreeComponent& OwnerComp);
	static int GetAvailableSlot(const UInventoryComponent* Inventory);
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Target;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GrabItem : public UBTTask_InventoryAccess
{
	GENERATED_BODY()
	
public:
	UBTTask_GrabItem();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
};
