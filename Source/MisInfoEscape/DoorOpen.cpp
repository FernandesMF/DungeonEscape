// Fill out your copyright notice in the Description page of Project Settings.
#define OUT

#include "DoorOpen.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Controller.h"


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
	//ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame. Checks if the condition to open or close the door are satisfied.
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Door opens if total mass over the trigger volume is bigger than the triggering mass
	if (TotalMassOverPressurePlate() > TriggerMass)
	{
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	// Door closes if enough time has passed since with the opening condition not being satisfied
	else if ( GetWorld()->GetTimeSeconds() - LastOpenTime > CloseDelay) {
		CloseDoor();
	}
}

void UDoorOpen::OpenDoor()
{	
	Owner->SetActorRotation(FRotator (0.f, -OpenAngle, 0.f));
}

void UDoorOpen::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
}

float UDoorOpen::TotalMassOverPressurePlate() {
	float TotalMass = 0.f;
		
	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	/// Iterate over all of them, adding their masses
	for (const auto* Actor : OverlappingActors) {
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}