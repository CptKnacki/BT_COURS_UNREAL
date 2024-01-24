// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomMoveToTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include <GameFramework/FloatingPawnMovement.h>

EBTNodeResult::Type UCustomMoveToTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	bNotifyTick = true;

	if(!currentPawn)
		currentPawn = brain->GetControlledPawn();

	return EBTNodeResult::InProgress;

}

void UCustomMoveToTask::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	Move();

	if(isAtTarget)
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
}

void UCustomMoveToTask::Move()
{
	if (!currentPawn)
		return;


	FVector _targetVector = brain->GetBlackboardComponent()->GetValueAsVector(targetVectorKey);
	FVector _origin = currentPawn->GetActorLocation();
	float _distance = FVector::Dist(_origin, _targetVector);

	isAtTarget = _distance <= acceptableRadius;

	if(isAtTarget)
		return;

	FVector _result = FMath::VInterpConstantTo(_origin, _targetVector, GetWorld()->DeltaTimeSeconds, moveSpeed);
	currentPawn->SetActorLocation(_result);
}
