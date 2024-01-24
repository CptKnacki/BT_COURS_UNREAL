// Fill out your copyright notice in the Description page of Project Settings.


#include "Alien_CaC.h"
#include <Kismet/KismetSystemLibrary.h>
#include "AlienAIController.h"
#include "BehaviorTree/BlackboardComponent.h"

AAlien_CaC::AAlien_CaC()
{
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Skeletal mesh");
	RootComponent = mesh;
}

void AAlien_CaC::BeginPlay()
{
	Super::BeginPlay();
	Init();

}

void AAlien_CaC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DetectPlayer();
	UpdateBehaviourTree();
	DrawDebug();
}

void AAlien_CaC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAlien_CaC::DetectPlayer()
{
	TArray<AActor*> _results;

	bool _hit = UKismetSystemLibrary::SphereOverlapActors(GetWorld(), GetActorLocation(), range, hitLayers, nullptr, TArray<AActor*>(), _results);

	if (_hit)
	{
		target = _results[0];
		bHasTargetInSight = true;

		return;
	}

	target = nullptr;
	bHasTargetInSight = false;
	
}

void AAlien_CaC::DrawDebug()
{
	DrawDebugSphere(GetWorld(), GetActorLocation(), range, 50, bHasTargetInSight ? FColor::Red : FColor::Yellow, false, -1, 0, 1.0f);
}

void AAlien_CaC::UpdateBehaviourTree()
{

	if (aiController)
	{
		aiController->GetBlackboardComponent()->SetValueAsBool(boolKeyName, bHasTargetInSight);

		if (target)
		{
			FVector _location = target->GetActorLocation();
			_location.Z = 0;
			aiController->GetBlackboardComponent()->SetValueAsVector(vectorKeyName, _location);
		}

	}
}

void AAlien_CaC::Init()
{
	TArray<AActor*> _actors;
	_actors.Empty();
	GetAttachedActors(_actors);

	aiController = Cast<ACustomAIController>(_actors[0]);
}

