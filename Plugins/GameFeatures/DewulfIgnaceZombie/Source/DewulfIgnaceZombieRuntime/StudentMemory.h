#pragma once

#include <vector>

#include "Components/ActorComponent.h"
#include "Zombies/BaseZombie.h"
#include "Village/House/House.h"
#include "PurgeZones/PurgeZone.h"
#include "Items/BaseItem.h"

#include "StudentMemory.Generated.h"

UCLASS()
class DEWULFIGNACEZOMBIERUNTIME_API UStudentMemory : public UActorComponent
{
	GENERATED_BODY()
	
public:
	UStudentMemory();
	
	virtual void TickComponent
	(
		float DeltaTime,
		enum ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction
	) override;
	
	void Memorize(ABaseZombie* Zombie);
	void Memorize(APurgeZone* PurgeZone);
	void Memorize(AHouse* House);
	void Memorize(ABaseItem* Item);
	
	void Forget(const ABaseZombie* Zombie);
	void Forget(const APurgeZone* PurgeZone);
	void Forget(const AHouse* House);
	void Forget(const ABaseItem* Item);
	
	const TArray<FVector>& GetPathToClosestHouse() const;
	
private:
	UFUNCTION()
	void Forget(AActor* Actor);
	void UpdatePaths();
	
	float TimeUntilPathUpdate{ 0.f };
	float MemoryRange{ 100.f };
	
	std::vector<const ABaseZombie*> Zombies{};
	std::vector<const APurgeZone*> PurgeZones{};
	std::vector<const AHouse*> Houses{};
	std::vector<const ABaseItem*> Items{};
	
	TArray<FVector> PathToClosestHouse{};
};
