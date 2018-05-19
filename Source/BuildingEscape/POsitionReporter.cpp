// Fill out your copyright notice in the Description page of Project Settings.

#include "POsitionReporter.h"
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPOsitionReporter::UPOsitionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPOsitionReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetActorLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s is at %s"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPOsitionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

