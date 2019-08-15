// Fill out your copyright notice in the Description page of Project Settings.
#define OUT

#include "DoorOpen.h"

// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("No pressure plate assigned to %s"), *Owner->GetName());
		return;
	}

	return;
}


// Called every frame. Checks if the condition to open or close the door are satisfied.
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate) { return; }

	// Door opens if total mass over the trigger volume is bigger than the triggering mass; closes otherwise
	if (TotalMassOverPressurePlate() > TriggerMass) { OpenRequest.Broadcast(); }
	else { CloseRequest.Broadcast(); }

	return;
}

float UDoorOpen::TotalMassOverPressurePlate() {
	float TotalMass = 0.f;
	if (!PressurePlate) { return TotalMass; }

	/// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);

	/// Iterate over all of them, adding their masses
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}