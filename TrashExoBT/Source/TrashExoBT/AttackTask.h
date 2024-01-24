// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TaskNode.h"
#include "AttackTask.generated.h"

/**
 * 
 */
UCLASS()
class TRASHEXOBT_API UAttackTask : public UTaskNode
{
	GENERATED_BODY()
	
protected: 
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
