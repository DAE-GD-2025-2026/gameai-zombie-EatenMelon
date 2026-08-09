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
	
	const std::vector<ABaseZombie*>& GetZombies() const;
	const std::vector<APurgeZone*>& GetPurgeZones() const;
	const std::vector<AHouse*>& GetHouses() const;
	const std::vector<ABaseItem*>& GetItems() const;
	
	UFUNCTION()
	void Forget(AActor* Actor);
	
private:
	void UpdatePaths();
	
	float TimeUntilPathUpdate{ 0.f };
	float MemoryRange{ 100.f };
	
	std::vector<ABaseZombie*> Zombies{};
	std::vector<APurgeZone*> PurgeZones{};
	std::vector<AHouse*> Houses{};
	std::vector<ABaseItem*> Items{};
	
	TArray<FVector> PathToClosestHouse{};
};
