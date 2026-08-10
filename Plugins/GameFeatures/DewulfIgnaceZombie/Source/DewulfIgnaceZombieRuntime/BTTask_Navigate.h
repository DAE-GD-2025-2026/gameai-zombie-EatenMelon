#pragma once

#include "BehaviorTree/BTTaskNode.h"
#include "StudentMemory.h"
#include "BTTask_Navigate.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_Navigate : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_Navigate();
	
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	
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
	
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector TargetKey;
	
	UPROPERTY(EditAnywhere, Category = "Measurements")
	float MinDistanceToZombies = 25.f;
	UPROPERTY(EditAnywhere, Category = "Measurements")
	float MinDistanceToPurgeZones = 125.f;
	
	UPROPERTY(EditAnywhere, Category = "Weights")
	float AvoidZombiesWeight{ 0.5f };
	UPROPERTY(EditAnywhere, Category = "Weights")
	float AvoidPurgeZonesWeight{ 0.5f };
	UPROPERTY(EditAnywhere, Category = "Weights")
	float SearchTargetWeight{ 0.5f };
	
private:
	UPROPERTY()
	TObjectPtr<AActor> TargetActor{ nullptr };
	FVector TargetLocation{ FVector::Zero() };
	
	UPROPERTY()
	TObjectPtr<UStudentMemory> StudentMemory{ nullptr };
	
	void UpdatePath(float DeltaSeconds);
	void CalculateSteering(UBehaviorTreeComponent& OwnerComp, float DeltaSeconds);
	
	float TimeUntilPathUpdate{ 0.f };
	int CurrentTargetNodeIndex{ 0 };
	TArray<FVector> Path{};
};
