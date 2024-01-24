// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTreePawnAI.h"

// Sets default values
ABehaviourTreePawnAI::ABehaviourTreePawnAI()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABehaviourTreePawnAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABehaviourTreePawnAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABehaviourTreePawnAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

