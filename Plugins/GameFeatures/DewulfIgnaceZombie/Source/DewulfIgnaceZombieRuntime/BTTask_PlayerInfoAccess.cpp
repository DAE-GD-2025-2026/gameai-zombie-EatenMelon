#include "BTTask_PlayerInfoAccess.h"
#include "AIController.h"
#include "Common/HealthComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Common/StaminaComponent.h"

UBTTask_GetHealthPercentage::UBTTask_GetHealthPercentage()
{
	NodeName = TEXT("Get Health Percent");
}

EBTNodeResult::Type UBTTask_GetHealthPercentage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	const float Percent = static_cast<float>(HealthComp->GetHealth()) / HealthComp->GetMaxHealth();
	
	UBlackboardComponent* BlackboardComponent = OwnerComp.GetBlackboardComponent();
	
	if (BlackboardComponent == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	BlackboardComponent->SetValueAsFloat(HealthPercent.SelectedKeyName, Percent);
	
	return EBTNodeResult::Succeeded;
}

UBTTask_GetStaminaPercentage::UBTTask_GetStaminaPercentage()
{
	NodeName = TEXT("Get Stamina Percent");
}

EBTNodeResult::Type UBTTask_GetStaminaPercentage::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
