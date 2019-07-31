// Fill out your copyright notice in the Description page of Project Settings.

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

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();
	ActorThatTriggers = GetWorld()->GetFirstPlayerController()->GetPawn();
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate && ActorThatTriggers && PressurePlate->IsOverlappingActor(ActorThatTriggers))
	{
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	if ( GetWorld()->GetTimeSeconds() - LastOpenTime > CloseDelay) {
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

