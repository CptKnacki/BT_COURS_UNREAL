// Fill out your copyright notice in the Description page of Project Settings.


#include "DetectionComponent.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UDetectionComponent::UDetectionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UDetectionComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UDetectionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Detect();
	Debug();
}

void UDetectionComponent::Detect()
{
	FHitResult _result;

	FVector _startLocation = GetOwner()->GetActorLocation();

	bool _hit = UKismetSystemLibrary::SphereTraceSingleForObjects(GetWorld(), _startLocation, _startLocation,
						detectionRange, layerToDetect, true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, _result, true);

	if (_hit)
	{
		target = _result.GetActor();
		targetDetected = true;
	}
	else
	{
		target = nullptr;	
		targetDetected = false;
	}

	onTargetFound.Broadcast(target);
	onTargetDetected.Broadcast(targetDetected);
}

void UDetectionComponent::Debug()
{
	//DrawDebugSphere(GetWorld(), GetOwner()->GetActorLocation(), detectionRange, 30, FColor::Yellow, false, -1, 0, 2.0f);
}

