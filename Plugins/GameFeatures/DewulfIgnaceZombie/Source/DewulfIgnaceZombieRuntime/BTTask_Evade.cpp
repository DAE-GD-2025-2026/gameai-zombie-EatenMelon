#include "BTTask_Evade.h"

UBTTask_Evade::UBTTask_Evade()
{
	NodeName = TEXT("Evade");
}

EBTNodeResult::Type UBTTask_Evade::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
