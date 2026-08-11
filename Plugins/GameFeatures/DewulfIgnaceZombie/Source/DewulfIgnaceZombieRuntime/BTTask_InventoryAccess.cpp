#include "BTTask_InventoryAccess.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Items/Food.h"
#include "Items/Medkit.h"
#include "Items/Pistol.h"

UInventoryComponent* UBTTask_InventoryAccess::GetInventory(const UBehaviorTreeComponent& OwnerComp)
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
	
	if (AIOwner == nullptr) return nullptr;
	
	const APawn* Pawn = AIOwner->GetPawn();
	
	if (Pawn == nullptr) return nullptr;
	
	return Pawn->FindComponentByClass<UInventoryComponent>();
}

int UBTTask_InventoryAccess::GetAvailableSlot(const UInventoryComponent* Inventory)
{
	if (Inventory == nullptr)
	{
		return -1;
	}
	
	const auto& Inv = Inventory->GetInventory();
	
	if(Inv.IsEmpty())
	{
		return 0;
	}
	
	for (int Slot{0}; Slot < Inv.Num(); ++Slot)
	{
		if (Inv[Slot] != nullptr) continue;
		return Slot;
	}
	
	GEngine->AddOnScreenDebugMessage
	(
		-1,
		5.f,
		FColor::Magenta,
		FString::Printf(TEXT("Inventory is full!"))
	);
	
	return -1;
}

UBTTask_GrabItem::UBTTask_GrabItem()
{
	NodeName = TEXT("Grab Item");
}

EBTNodeResult::Type UBTTask_GrabItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UInventoryComponent* Inventory = GetInventory(OwnerComp);
	
	if (Inventory == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const int Slot = GetAvailableSlot(Inventory);
	
	if (Slot < 0)
	{
		return EBTNodeResult::Failed;
	}
	
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	AActor* TargetActor = 
		Cast<AActor>(BlackboardComponent->GetValueAsObject(Target.SelectedKeyName));
	
	if (TargetActor == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	ABaseItem* Item = Cast<ABaseItem>(TargetActor);
	
	if (Item == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if(!Inventory->GrabItem(Slot, Item))
	{
		return EBTNodeResult::Failed;
	}
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}

UBTTask_SelectItem::UBTTask_SelectItem()
{
	NodeName = TEXT("Select Item");
}

EBTNodeResult::Type UBTTask_SelectItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UInventoryComponent* InventoryComp = GetInventory(OwnerComp);
	
	if (InventoryComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	TArray<ABaseItem*> Inventory = InventoryComp->GetInventory();
	
	if (Inventory.IsEmpty())
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	int Slot{};
	for (Slot = 0; Slot < Inventory.Num(); ++Slot)
	{
		if (IsOfCategory(Inventory[Slot], ItemCategory))
		{
			BlackboardComponent->SetValueAsInt(ItemSlot.SelectedKeyName, Slot);
			
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;
}

bool UBTTask_SelectItem::IsOfCategory(const ABaseItem* Item, EItemCategory Category)
{
	if (Item == nullptr) return false;
	
	switch (Category)
	{
	case EItemCategory::Recovery:
		return Item->IsA<AFood>();
		
	case EItemCategory::Healing:
		return Item->IsA<AMedkit>();
		
	case EItemCategory::Weapon:
		return Item->IsA<AWeapon>();
	}
	
	return false;
}

EBTNodeResult::Type UBTTask_UseSelectedItem::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const int Slot = BlackboardComponent->GetValueAsInt(ItemSlot.SelectedKeyName);
	
	UInventoryComponent* InventoryComponent = GetInventory(OwnerComp);
	
	if (InventoryComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	TArray<ABaseItem*> Inventory = InventoryComponent->GetInventory();
	
	if (Slot >= Inventory.Num())
	{
		return EBTNodeResult::Failed;
	}
	
	if (Inventory[Slot] == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	if (Inventory[Slot]->GetValue() <= 0)
	{
		InventoryComponent->RemoveItem(Slot);
		return EBTNodeResult::Failed;
	}
	
	InventoryComponent->UseItem(Slot);
	
	if (Inventory[Slot]->GetValue() <= 0)
	{
		InventoryComponent->RemoveItem(Slot);
	}
	
	return EBTNodeResult::Succeeded;
}
