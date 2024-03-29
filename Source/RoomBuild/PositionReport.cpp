// Fill out your copyright notice in the Description page of Project Settings.


#include "PositionReport.h"
#include "Gameframework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	
	PrimaryComponentTick.bCanEverTick = true;

	
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	
	FString ObjectName = GetOwner()->GetName();

	//*My first try and it work hahaha*//
	/*FVector ObjectPos = GetOwner()->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s for %s"), *ObjectName, *ObjectPos.ToString());*/

	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToCompactString();
	UE_LOG(LogTemp, Warning, TEXT("%s for %s"), *ObjectName, *ObjectPos);
	
	
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

