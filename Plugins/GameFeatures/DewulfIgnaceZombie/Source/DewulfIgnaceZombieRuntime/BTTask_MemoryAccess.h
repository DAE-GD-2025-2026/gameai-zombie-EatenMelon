#pragma once

#include "StudentMemory.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MemoryAccess.generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_MemoryAccess : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	static UStudentMemory* GetStudentMemory(const UBehaviorTreeComponent& OwnerComp);
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Target;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_Forget final : public UBTTask_MemoryAccess
{
	GENERATED_BODY()
	
public:
	UBTTask_Forget();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetClosestHouse final : public UBTTask_MemoryAccess
{
	GENERATED_BODY()
	
public:
	UBTTask_GetClosestHouse();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
};

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UBTTask_GetClosestItem final : public UBTTask_MemoryAccess
{
	GENERATED_BODY()
	
public:
	UBTTask_GetClosestItem();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
};

UCLASS()
class UBTTask_GetClosestZombie final : public UBTTask_MemoryAccess
{
	GENERATED_BODY()

public:
	UBTTask_GetClosestZombie();
	
	virtual EBTNodeResult::Type ExecuteTask
	(
		UBehaviorTreeComponent& OwnerComp,
		uint8* NodeMemory
	) override;
	
};
