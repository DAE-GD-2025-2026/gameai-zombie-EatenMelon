#pragma once

#include "StudentMemory.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MemoryAccess.generated.h"

UCLASS()
class UBTTask_MemoryAccess : public UBTTaskNode
{
	GENERATED_BODY()
	
protected:
	static UStudentMemory* GetStudentMemory(UBehaviorTreeComponent& OwnerComp);
	
public:
	UPROPERTY(EditAnywhere, Category = "Blackboard")
	FBlackboardKeySelector Output;
};

UCLASS()
class UBTTask_GetClosestHouse : public UBTTask_MemoryAccess
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
