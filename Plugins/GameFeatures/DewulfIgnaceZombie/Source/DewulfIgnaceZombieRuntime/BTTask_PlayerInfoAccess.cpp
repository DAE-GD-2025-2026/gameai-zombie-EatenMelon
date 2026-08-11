#include "BTTask_PlayerInfoAccess.h"
#include "AIController.h"
#include "Common/HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/StaminaComponent.h"

UBTTask_GetHealthPercent::UBTTask_GetHealthPercent()
{
	NodeName = TEXT("Get Health Percent");
}

EBTNodeResult::Type UBTTask_GetHealthPercent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
	
	if (AIOwner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const APawn* Pawn = AIOwner->GetPawn();
	
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const UHealthComponent* HealthComp = Pawn->FindComponentByClass<UHealthComponent>();
	
	if (HealthComp == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const float Percent = HealthComp->GetHealth() / HealthComp->GetMaxHealth();
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsFloat(HealthPercent.SelectedKeyName, Percent);
	
	return EBTNodeResult::Succeeded;
}

UBTTask_GetStaminaPercent::UBTTask_GetStaminaPercent()
{
	NodeName = TEXT("Get Stamina Percent");
}

EBTNodeResult::Type UBTTask_GetStaminaPercent::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* AIOwner = OwnerComp.GetAIOwner();
	
	if (AIOwner == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const APawn* Pawn = AIOwner->GetPawn();
	
	if (Pawn == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const UStaminaComponent* StaminaComponent = Pawn->FindComponentByClass<UStaminaComponent>();
	
	if (StaminaComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	const float Percent = StaminaComponent->GetCurrentStamina() / StaminaComponent->GetMaxStamina();
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsFloat(StaminaPercent.SelectedKeyName, Percent);
	
	return EBTNodeResult::Succeeded;
}
