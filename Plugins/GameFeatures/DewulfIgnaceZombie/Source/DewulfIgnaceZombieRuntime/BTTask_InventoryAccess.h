#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "Common/InventoryComponent.h"
#include "BTTask_InventoryAccess.generated.h"

UENUM()
enum class EItemCategory
{
	Recovery UMETA(DisplayName = "Recovery"),
	Healing UMETA(DisplayName = "Healing"),
	Weapon UMETA(DisplayName = "Weapon"),
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_InventoryAccess: public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	static UInventoryComponent* GetInventory(const UBehaviorTreeComponent& OwnerComp);
	static int GetAvailableSlot(const UInventoryComponent* Inventory);
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
	
	UPROPERTY(EditAnywhere, Category = "Input")
	FBlackboardKeySelector Target;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_SelectItem : public UBTTask_InventoryAccess
{
	GENERATED_BODY()
	
public:
	UBTTask_SelectItem();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
	UPROPERTY(EditAnywhere, Category = "Output")
	FBlackboardKeySelector ItemSlot;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	EItemCategory ItemCategory;
	
private:
	static bool IsOfCategory(const ABaseItem* Item, EItemCategory Category);
	
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_UseSelectedItem : public UBTTask_InventoryAccess
{
	GENERATED_BODY()
public:
	UBTTask_UseSelectedItem();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
		
	UPROPERTY(EditAnywhere, Category = "Input")
    FBlackboardKeySelector ItemSlot;
};
