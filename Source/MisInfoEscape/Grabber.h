// Grabber component for the player pawn.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Public/CollisionQueryParams.h"
#include "Public/DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Components/PrimitiveComponent.h"

#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MISINFOESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame. Moves the grabbed object around, following the end of the reaching ray of the pawn.
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	/// The grabbing system will be based on ray-casting from the player position in his/her looking direction,
	/// up to a certian reach distance. These are the ray-casting variables and method. Since this mechanic is central
	/// in this game, they will be "global" in this class, instead of having rtestricted scope inside of a function.
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	float Reach = 100.0f;				// reaching distance in cm
	FVector LineTraceEnd;
	void RayCastReach();

	UPhysicsHandleComponent* PhysicsHandle = nullptr;	// Dummy initialization of physics handle
	void FindPhysicsHandleComponent();					// Finds physics handle of the player pawn

	UInputComponent* InputComponent = nullptr;		// Dummy initialization to the input component of player pawn
	void SetupInputComponent();						// Binds contoller input to actions
	
	FHitResult GetFirstPhysicsBodyHandleInReach();	// Ray-casts up to the reaching distance and returns the first object hit, if any
	void Grab();									// Grabs the object returned from ray-cast hit, if any
	void Release();									// Releases the grabbed object
	
};
