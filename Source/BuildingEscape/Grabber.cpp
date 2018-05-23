// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h" // required for GetWord()
#include "DrawDebugHelpers.h" // required for DrawDebugLine()

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
//	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get player viewpoint this tick
	FVector PlayerViewpointLocation;
	FRotator PlayerViewpointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		PlayerViewpointLocation,
		PlayerViewpointRotation
	);
	//UE_LOG(LogTemp, Warning, TEXT("Viewport Location: %s"), *PlayerViewPointLocation.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("Viewport rotation: %s"), *PlayerViewpointRotation.ToString())
	//UE_LOG(LogTemp, Warning, TEXT("========================"));

//	FVector LineTraceEnd = PlayerViewpointLocation + FVector(0.0f, 0.0f, 20.0f);

	FVector LineTraceDirection = PlayerViewpointRotation.Vector();
	/// Direction in which the toon is looking
	FVector LineTraceEnd = PlayerViewpointLocation + LineTraceDirection * Reach;

	/// Draw a red trace in the world to visualise
	DrawDebugLine(
		GetWorld(),
		PlayerViewpointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.0f,
		0.0f,
		4.0f
		);

	/// Set up query parameters
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	/// Line-trace (AKA Ray-cast) out to reach distance
	FHitResult Hit;
	bool HaveHitSomething = GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewpointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit
	///Hit.Actor->GetName()
	if (HaveHitSomething)
          UE_LOG(LogTemp, Warning, TEXT("We've hit object: %s"), *Hit.Actor->GetName())

}

