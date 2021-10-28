// Copyright Tom TMFK 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Misc/DateTime.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ROOMBUILD_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor()
	{

		Owner->SetActorRotation(FRotator(0.f, OpenAngle, 0.f));
	}

	void CloseDoor()
	{

		Owner->SetActorRotation(FRotator(0.f, 0.f, 0.f));
	}

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90.0f;
	
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
	float DoorCloseDelay =1.f;

	float LastDoorOpenTime;

	AActor* ActorThatOpens;// Remember pawn inherits from actor
	AActor* Owner; // the owning door
};
