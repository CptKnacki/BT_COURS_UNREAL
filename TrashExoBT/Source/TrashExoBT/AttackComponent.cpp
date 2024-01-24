// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackComponent.h"
#include <Kismet/KismetSystemLibrary.h>

// Sets default values for this component's properties
UAttackComponent::UAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UAttackComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(!canAttack)
	currentTime = UpdateTime(currentTime, maxTime);

	isInRange = CheckIsInRange(attackRange);
}



void UAttackComponent::Attack()
{
	if (!isInRange || !canAttack || !target)
		return;

	canAttack = false;
	FVector _loc = GetOwner()->GetActorLocation() + GetOwner()->GetActorForwardVector() * boxOffset;
	FRotator _rot = GetOwner()->GetActorRotation();
	FHitResult _result;
	bool _hit = UKismetSystemLibrary::BoxTraceSingleForObjects(GetWorld(), _loc, _loc, FVector(attackBoxSize), _rot, layer,
									true, TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, _result, true);


	if (_hit)
	{
		AActor* _target = _result.GetActor();

		if (target != _target)
			return;

		// TODO DEAL DMG
	}

}

float UAttackComponent::UpdateTime(float _current, const float& _max)
{
	_current += GetWorld()->DeltaTimeSeconds * attackSpeed;
	if (_current >= _max)
	{
		canAttack = true;
		_current = 0;
	}

	return _current;
}

bool UAttackComponent::CheckIsInRange(const float& _range)
{
	if (!target)
		return false;
	
	float _distance = FVector::Dist(GetOwner()->GetActorLocation(), target->GetActorLocation());

	const bool _value = _distance <= _range;
	onRangeUpdate.Broadcast(_value);

	return _value;
}

void UAttackComponent::SetTarget(AActor* _target)
{
	target = _target;
}
