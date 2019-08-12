// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {

	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle component..."), *GetOwner()->GetName() );
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// Get player POV
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Log it out
	/*UE_LOG(LogTemp, Warning, TEXT("Player Location: %s\n"), *(PlayerViewPointLocation.ToString()));
	UE_LOG(LogTemp, Warning, TEXT("Player Rotation: %s\n"), *(PlayerViewPointRotation.ToString()));
	*/

	/// Cast ray up to a given distance
	LineTraceEnd = PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,
		LineTraceEnd,
		FColor(255, 0, 0),
		false,
		0.f,
		0,
		5.0f
	);

	/// Check what is being reached
	FHitResult Hit;
	FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody)	
	);
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()) );
	}
	//UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(Hit.GetActor()->GetName()) );

	/// Grab it...
}

