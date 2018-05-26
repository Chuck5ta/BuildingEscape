// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h" // required for GetWord()

#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PreasurePlate)
		UE_LOG(LogTemp, Warning, TEXT("%s missing pressure plate"), *GetOwner()->GetName());
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnOpen.Broadcast();
	// Poll the Trigger Volume
	if (GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO make into a parameter
	{
		// If the ActorThatOpens is in the volume
		OnOpen.Broadcast();
	}
	else
	{
		// If the ActorThatOpens is in the volume
		OnClose.Broadcast();
	}
		
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float ToTalMass = 0.0f;

	// Find all the overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PreasurePlate)
    PreasurePlate->GetOverlappingActors(OUT OverlappingActors);
	else
		return 0.0f;

	// Iterate through them adding their masses
	for (const auto& AnActor : OverlappingActors)
	{
		ToTalMass += AnActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s on pressure plate"), *AnActor->GetName());
	}

	return ToTalMass;
}




