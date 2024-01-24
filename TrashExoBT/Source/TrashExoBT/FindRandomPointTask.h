// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskNode.h"
#include "FindRandomPointTask.generated.h"

/**
 * 
 */
UCLASS()
class TRASHEXOBT_API UFindRandomPointTask : public UTaskNode
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) FVector randomLocation = FVector(0);
	UPROPERTY(EditAnywhere) float radius = 2000;
	UPROPERTY(EditAnywhere) FName patrolLocationKeyName = "patrolLocation";

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
