#pragma once
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_Face.generated.h"

UCLASS()
class UBTTask_Face final : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Face();
	
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
	
	UPROPERTY(EditAnywhere, Category = "Input")
	FBlackboardKeySelector Target;
	
	UPROPERTY(EditAnywhere, Category = "Settings")
	float MaxAngularVelocity{500};
	
private:
	UPROPERTY()
	TObjectPtr<AActor> TargetActor{nullptr};
	
	UPROPERTY()
	TObjectPtr<APawn> Pawn{nullptr};
	
	float AngularVelocity{0.f};
};
