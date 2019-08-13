// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetupInputComponent();	
}

// Finds physics handle component (assumed to be) attached to the default pawn
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle component..."), *GetOwner()->GetName());
	}
}

// Binds actions to the input component
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("Found input component for %s!"), *GetOwner()->GetName());
		/// Bind the input actions
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s has no input component..."), *GetOwner()->GetName());
	}
}

// Gets physics handle of the object hit by ray-casting  
void UGrabber::Grab() 
{
	UE_LOG(LogTemp, Warning, TEXT("Tried to grab."));
	// Get component and actor from hit result (might be nothing)
	FHitResult HitResult = GetFirstPhysicsBodyHandleInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* HitActor = HitResult.GetActor();
	
	// If we hit something, then grab that component, constraining rotation
	if (HitActor != nullptr) {
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			ComponentToGrab,
			NAME_None,
			ComponentToGrab->GetOwner()->GetActorLocation(),
			ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}

	return;
}

// Ray-casts from player position, and returns Hit if there was an object in reach
FHitResult UGrabber::GetFirstPhysicsBodyHandleInReach()
{
	/// Get player POV
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	/// Cast ray up to a given distance
	LineTraceEnd = PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();

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
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(ActorHit->GetName()));
	}

	return Hit;
}

// Releases the object physics handle
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released grab."));
	PhysicsHandle->ReleaseComponent();
	return;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// If a physics handle of an object is attached
	if (PhysicsHandle != nullptr) {
		// Move the object being held to the end of player "reach line"
		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);
		LineTraceEnd = PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
		
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}
		

