#include "BTTask_Seek.h"

UBTTask_Seek::UBTTask_Seek()
{
	NodeName = TEXT("Seek");
}

EBTNodeResult::Type UBTTask_Seek::ExecuteTask
(
	UBehaviorTreeComponent& OwnerComp,
	uint8* NodeMemory
)
{
	APawn* Pawn = Cast<APawn>(OwnerComp.GetOwner());
	AActor* Target = reinterpret_cast<AActor*>(NodeMemory);
	
	
	
	return Super::ExecuteTask(OwnerComp, NodeMemory);
}
