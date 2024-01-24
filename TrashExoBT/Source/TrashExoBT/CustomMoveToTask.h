// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskNode.h"
#include "CustomMoveToTask.generated.h"

/**
 * 
 */
UCLASS()
class TRASHEXOBT_API UCustomMoveToTask : public UTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) float moveSpeed = 500;
	UPROPERTY(EditAnywhere) float acceptableRadius = 50;
	UPROPERTY(EditAnywhere) FName targetVectorKey;
	UPROPERTY() TObjectPtr<APawn> currentPawn = nullptr;
	bool isAtTarget = false;
protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	void Move();
};
