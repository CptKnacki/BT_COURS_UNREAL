// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienAIController.h"

ACustomAIController::ACustomAIController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ACustomAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACustomAIController::Init()
{
	controlledPawn = GetPawn();

	if (!controlledPawn)
		return;

	bAttachToPawn = true;
	AttachToPawn(controlledPawn);
	RunBehaviorTree(tree);

}