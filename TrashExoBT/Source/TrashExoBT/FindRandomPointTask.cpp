// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomPointTask.h"
#include <NavigationSystem.h>
#include "BehaviorTree/BlackboardComponent.h"

EBTNodeResult::Type UFindRandomPointTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UNavigationSystemV1* _nav = UNavigationSystemV1::GetCurrent(GetWorld());

	FVector _origin = brain->GetControlledPawn()->GetActorLocation();
	FNavLocation _point;
	bool _success = _nav->GetRandomPointInNavigableRadius(_origin, radius, _point);

	if (!_success)
	{
		return EBTNodeResult::Failed;
	}

	randomLocation = _point.Location;
	randomLocation.Z = 0;
	brain->GetBlackboardComponent()->SetValueAsVector(patrolLocationKeyName, randomLocation);

	return EBTNodeResult::Succeeded;
}
