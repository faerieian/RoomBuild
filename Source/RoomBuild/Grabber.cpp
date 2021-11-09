// Copyright Tom TMFK 2021


#include "Grabber.h"
#include "Gameframework/Actor.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

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

	FindPhysicsHandleComponent();
	SetupInputComponent();

	
}




void UGrabber::FindPhysicsHandleComponent()
{
	/// Look for attached Physics Handle

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component "), *GetOwner()->GetName());
	}
	
}
void UGrabber::SetupInputComponent()
{
	/// Look for attached Input component ( only appears at run time )
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s Found input component "), *GetOwner()->GetName());
		/// Bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}
void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab pressed "));

	/// Line TRACE and see if we reach any actors with physics body collision channel set 
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent(); // gets the mesh in our case
	auto ActorHit = HitResult.GetActor();

	/// if we hit something then attach a physics handle
	if (ActorHit)
	{
		/// this function Ben teach me but i have too change by myself because unreal warning project will no longer compile sorry ben
		 PhysicsHandle->GrabComponent(
			ComponentToGrab, // turn out to be the mesh
			NAME_None, // no bones needed
			ComponentToGrab->GetOwner()->GetActorLocation(),
			true); // allow rotation

		/// this my try to write method by myself haha
		if (!PhysicsHandle) { return; }
		//PhysicsHandle->GrabComponentAtLocationWithRotation(
		//	ComponentToGrab, // turn out to be the mesh
		//	NAME_None, // no bones needed
		//	ComponentToGrab->GetOwner()->GetActorLocation(),
		//	ComponentToGrab->GetOwner()->GetActorRotation());
	}
	
}
FVector UGrabber::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;

}
FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

}
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{

	/// Line-race (AKA ray-cast) out to reach distance
	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner()); /// Setup query parameters
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	/// See what we hit 
	//AActor* ActorHit = Hit.GetActor();
	//if (ActorHit)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Line trace hit: %s"), *ActorHit->GetName());
	//}
	//else
	//{
	//	/*UE_LOG(LogTemp, Warning, TEXT("Line trace doesn't hit"));*/
	//}
	return HitResult;
}
void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab released "));
	//if (!PhysicsHandle) { return; }
	PhysicsHandle->ReleaseComponent();
}





// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (!PhysicsHandle) { return; }
	// if the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{

		// move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
	
}


