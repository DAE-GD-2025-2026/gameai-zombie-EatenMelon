// Fill out your copyright notice in the Description page of Project Settings.


#include "StudentPerceptor.h"

#include "StudentMemory.h"
#include "Items/BaseItem.h"
#include "Zombies/BaseZombie.h"
#include "Village/House/House.h"
#include "Perception/AIPerceptionTypes.h"
#include "PurgeZones/PurgeZone.h"

UStudentPerceptor::UStudentPerceptor()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UStudentPerceptor::BeginPlay()
{
	Super::BeginPlay();
	
	if (const auto PerceptionComp = GetOwner()->GetComponentByClass<UAIPerceptionComponent>())
	{
		PerceptionComp->OnTargetPerceptionUpdated.AddDynamic(this, &UStudentPerceptor::OnPerceptionUpdated);
	}
	
	Memory = NewObject<UStudentMemory>(GetOwner());
	Memory->RegisterComponent();
}

void UStudentPerceptor::OnPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Memory == nullptr) return;
	
	if (auto Zombie = Cast<ABaseZombie>(Actor))
	{
		Memory->Memorize(Zombie);
	}
	else if (auto PurgeZone = Cast<APurgeZone>(Actor))
	{
		Memory->Memorize(PurgeZone);
	}
	else if (auto House = Cast<AHouse>(Actor))
	{
		Memory->Memorize(House);
	}
	else if (auto Item = Cast<ABaseItem>(Actor))
	{
		Memory->Memorize(Item);
	}
	
	// Stimulus does not appear
	// if (Stimulus.Type == UAISense::GetSenseID<UAISense_Damage>())
	// {
	// 	message	= TEXT("Damage perceived!");
	// }
	
	// auto Owner = Cast<ASurvivorPawn>(GetOwner());
	// auto Movement = Owner->FindComponentByClass<UFloatingPawnMovement>();
	//
	// if (Movement != nullptr)
	// {
	// 	// Movement->Velocity += FVector(100000.f, 0.f, 0.f);
	// 	// Owner->AddMovementInput()
	// }
}
