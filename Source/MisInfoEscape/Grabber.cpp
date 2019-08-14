
#define OUT
#include "Grabber.h"

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

// Finds physics handle component (assumed to be) attached to the pawn
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("%s has no physics handle component..."), *GetOwner()->GetName());
	}
	return;
}

// Binds actions to the input component of the pawn.
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("%s has no input component..."), *GetOwner()->GetName());
	}
	return;
}

// Called when the input event assigned to "Grab" is triggered. Grabs the component
// that was returned from ray-cast hit (if any)
void UGrabber::Grab() 
{
	// Get component and actor from hit result (might be nothing)
	FHitResult HitResult = GetFirstPhysicsBodyHandleInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();
	AActor* HitActor = HitResult.GetActor();
	
	// If we hit something, then grab that component, constraining rotation
	if (!PhysicsHandle) { return; }
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

// Called when the input event assigned to "Release" is triggered. Releasess the component
// that is grabbed by the physics handle.
void UGrabber::Release()
{
	if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
	return;
}

// Returns Hit if there was an object in reach 
FHitResult UGrabber::GetFirstPhysicsBodyHandleInReach()
{
	RayCastReach();
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

	return Hit;
}

// Casts ray from player position in the direction he/she is looking, up to the reaching distance
void UGrabber::RayCastReach() {
	/// Get player POV
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);
	LineTraceEnd = PlayerViewPointLocation + Reach * PlayerViewPointRotation.Vector();
	return;
}

// Called every frame. Moves the grabbed object around, following the end of the reaching ray of the pawn.
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// If a physics handle of an object is attached
	if (PhysicsHandle != nullptr) {
		// Update its position to the end of player's "reach line"
		RayCastReach();		
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
	return;
}