// Fill out your copyright notice in the Description page of Project Settings.


#include "Octree.h"
#include "OctreeCell.h"
#include <NavigationSystem.h>

// Sets default values
AOctree::AOctree()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");
}

void AOctree::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOctree::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AOctree::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AOctree::InitRootCell()
{
	if (!root)
		return;

	UNavigationSystemV1* _nav = UNavigationSystemV1::GetCurrent(GetWorld());
	
	if (!_nav)
		return;

	FVector _navigableBounds = _nav->GetNavigableWorldBounds().GetExtent();

	FTimerHandle _timer;
	FTimerDelegate _delegate;

	_delegate.BindUObject(root, &AOctreeCell::SetCellDimensions, _navigableBounds.X, _navigableBounds.Y, _navigableBounds.Z);
	GetWorld()->GetTimerManager().SetTimer(_timer, _delegate, 2.0f, false, 0.1f);

	root->AttachToActor(this, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	root->SetOctree(this);
}

void AOctree::GenerateOctree()
{
	if (root)
		return;

	root = GetWorld()->SpawnActor<AOctreeCell>(cellToSpawn, GetActorLocation(), FRotator::ZeroRotator);


	if (!root)
	{
		UE_LOG(LogTemp, Warning, TEXT("ERROR : FAILED TO ROOT"));
		return;
	}
	InitRootCell();
}

void AOctree::DestroyOctree()
{
	if (!root)
		return;

	root->CustomDestroy();

	Destroy();
}
