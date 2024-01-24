// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackTask.h"
#include "Enemy.h"
#include "AttackComponent.h"

EBTNodeResult::Type UAttackTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	AEnemy* _enemy = Cast<AEnemy>(brain->GetControlledPawn());

	if (!_enemy)
		return EBTNodeResult::Failed;

	_enemy->GetAttack()->Attack();


	return EBTNodeResult::Succeeded;
}
