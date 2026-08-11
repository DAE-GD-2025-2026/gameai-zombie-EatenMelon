#include "BTTask_InventoryAccess.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"

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
