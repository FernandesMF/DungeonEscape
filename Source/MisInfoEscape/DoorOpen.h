// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "Components/PrimitiveComponent.h"
#include "Gameframework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
//#include "GameFramework/Controller.h"

#include "DoorOpen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOpenRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MISINFOESCAPE_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OpenDoor();
	void CloseDoor();
	float TotalMassOverPressurePlate();

	UPROPERTY(BlueprintAssignable)
	FOpenRequest OpenRequest;

private:
	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;

	UPROPERTY(EditAnywhere)
	float CloseDelay = 0.3f;

	UPROPERTY(EditAnywhere)
	float TriggerMass = 30.f;

	float LastOpenTime = 0.0f;

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;

	AActor* Owner = nullptr;
};
