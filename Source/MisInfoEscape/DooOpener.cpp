// Fill out your copyright notice in the Description page of Project Settings.

#include "DooOpener.h"
#include "Gameframework/Actor.h"

// Sets default values for this component's properties
UDooOpener::UDooOpener()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDooOpener::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();
	FRotator NewRotation (0.f, -60.f, 0.f);
	Owner->SetActorRotation(NewRotation);
}


// Called every frame
void UDooOpener::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

