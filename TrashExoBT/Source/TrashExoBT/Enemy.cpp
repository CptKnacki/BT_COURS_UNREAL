// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AttackComponent.h"
#include "AlienAIController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	skeleton = CreateDefaultSubobject<USkeletalMeshComponent>("skeleton");
	RootComponent = skeleton;

	detection = CreateDefaultSubobject<UDetectionComponent>("DetectionComponent");
	AddOwnedComponent(detection);

	attack = CreateDefaultSubobject<UAttackComponent>("Attack");
	AddOwnedComponent(attack);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	Init();
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemy::Init()
{
	if (!detection)
		return;

	aiController = Cast<ACustomAIController>(GetController());

	if (!aiController)
		return;

	detection->OnTargetFound().AddDynamic(aiController, &ACustomAIController::ReceiveTarget);
	detection->OnTargetDetected().AddDynamic(aiController, &ACustomAIController::ReceiveTargetDetected);


	if (!attack)
		return;

	attack->OnRangeUpdate().AddDynamic(aiController, &ACustomAIController::ReceiveIsInRange);
	detection->OnTargetFound().AddDynamic(attack, &UAttackComponent::SetTarget);
}

