// Fill out your copyright notice in the Description page of Project Settings.


#include "AlienAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

ACustomAIController::ACustomAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACustomAIController::ReceiveTarget(AActor* _target)
{
	Blackboard->SetValueAsObject(keyTarget, _target);
}

void ACustomAIController::ReceiveTargetDetected(bool _value)
{
	Blackboard->SetValueAsBool(keyDetected, _value);
}

void ACustomAIController::ReceiveIsInRange(bool _value)
{
	Blackboard->SetValueAsBool(keyIsInRange, _value);
}

void ACustomAIController::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void ACustomAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Debug();
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

void ACustomAIController::Debug()
{
	const FVector _location = Blackboard->GetValueAsVector(patrolLocKeyName);
	DrawDebugSphere(GetWorld(), _location, 200, 30, FColor::Red, false, -1, 0, 3.0f);
}
