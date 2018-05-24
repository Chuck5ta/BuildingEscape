// Fill out your copyright notice in the Description page of Project Settings.

#include "GameFramework/Actor.h"
#include "Engine/World.h" // required for GetWord()
#include "DrawDebugHelpers.h" // required for DrawDebugLine()
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

/// Look for attached Physics Handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle)
	{
		// PhysicsHandle is found
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Physics handle is missing for: %s"), *GetOwner()->GetName())
	}
}

/// Look for attached Input Component (only appears at run time)
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component found for: %s"), *GetOwner()->GetName());
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Input component MISSING %s"), *GetOwner()->GetName());
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));

	/// LINE TRACE and see if we reach any actors with physics body collision channel set (active)
	GFirstPhysicsBodyInReach();

	/// If we hit something, then attach a physics handle
	// TODO attach physics handle
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
	// TODO release physics handle
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	    // move the object that we're holding

}

const FHitResult UGrabber::GFirstPhysicsBodyInReach()
{
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
	/// Hit.Actor->GetName()
	if (HaveHitSomething)
	{
		UE_LOG(LogTemp, Warning, TEXT("We've hit object: %s"), *Hit.Actor->GetName())
	}

	return FHitResult();
}

