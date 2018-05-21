// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
//#include "GameFramework/Actor.h"
#include "Engine/World.h" // required for GetWord()


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

	AnActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UOpenDoor::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}

void UOpenDoor::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.0f, CloseAngle, 0.0f));
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (PreasurePlate->IsOverlappingActor(AnActorThatOpens))
	{
		// If the ActorThatOpens is in the volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetRealTimeSeconds();
	}

	// Check if it's time to close the door
	if (GetWorld()->GetRealTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
	{
		// If the ActorThatOpens is in the volume
		CloseDoor();
	}

	
}




