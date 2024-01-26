// Fill out your copyright notice in the Description page of Project Settings.


#include "OctreeCell.h"
#include "Octree.h"

// Sets default values
AOctreeCell::AOctreeCell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

	box = CreateDefaultSubobject<UBoxComponent>("Box");
	box->SetupAttachment(RootComponent);
}

void AOctreeCell::SetCellDimensions(const double _length, const double _width, const double _height)
{
	box->SetBoxExtent(FVector(_length, _width, _height));
}

void AOctreeCell::SetCellDimension(const FVector& _dimensions)
{
	box->SetBoxExtent(_dimensions);
}

// Called when the game starts or when spawned
void AOctreeCell::BeginPlay()
{
	Super::BeginPlay();
	onNumberOfActorsInsideUpdate.AddDynamic(this, &AOctreeCell::ManageCellBehvaiour);
}

// Called every frame
void AOctreeCell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebug();
}

bool AOctreeCell::ShouldTickIfViewportsOnly() const
{
	return true;
}


void AOctreeCell::CustomDestroy()
{

	for (size_t i = 0; i < currentNumberOfChildren; i++)
	{
		AOctreeCell* _cell = cellChildren[i];

		if (!_cell)
			continue;

		_cell->CustomDestroy();
	}

	cellChildren.Empty();
	Destroy();
}


void AOctreeCell::NotifyActorBeginOverlap(AActor* _otherActor)
{
	Super::NotifyActorBeginOverlap(_otherActor);
	
	const int _size = classToDetect.Num();
	for (size_t i = 0; i < _size; i++)
	{
		if (classToDetect[i].GetDefaultObject()->StaticClass() == _otherActor->StaticClass())
		{
			currentActorsInside++;
			actorsInSight.Add(_otherActor);
		}
	}

	onNumberOfActorsInsideUpdate.Broadcast(currentActorsInside);
}

void AOctreeCell::NotifyActorEndOverlap(AActor* _otherActor)
{
	Super::NotifyActorEndOverlap(_otherActor);

	const int _size = classToDetect.Num();
	for (size_t i = 0; i < _size; i++)
	{
		if (classToDetect[i].GetDefaultObject()->StaticClass() == _otherActor->StaticClass())
		{
			currentActorsInside--;
			actorsInSight.Remove(_otherActor);
		}
	}

	onNumberOfActorsInsideUpdate.Broadcast(currentActorsInside);
}

void AOctreeCell::InitSubCell(const int _branchingID, AOctree* _octree, AOctreeCell* _parent)
{
	branchingID = _branchingID + 1;
	octree = _octree;
	parent = _parent;
}

void AOctreeCell::SubDivideCell(const FVector _subLocation)
{
	AOctreeCell* _subCell = GetWorld()->SpawnActor<AOctreeCell>(octree->GetOctreeCellToSpawn(), GetActorLocation(), FRotator::ZeroRotator);

	if (!_subCell)
		return;

	_subCell->InitSubCell(branchingID, octree, this);
	_subCell->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
	_subCell->box->SetBoxExtent(box->GetScaledBoxExtent() /2);
	_subCell->SetActorLocation(_subLocation);

	cellChildren.Add(_subCell);
	currentNumberOfChildren++;
}

void AOctreeCell::RemoveSubCells()
{
	if (branchingID < 2) 
		return;

	for (size_t i = 0; i < currentNumberOfChildren; i++)
	{
		AOctreeCell* _cell = cellChildren[i];
		if (!_cell)
			continue;
		_cell->CustomDestroy();
	}
	cellChildren.Empty();
	currentNumberOfChildren = 0;
}

void AOctreeCell::ManageCellBehvaiour(const int _numberOfActorsInside)
{
	if (!octree)
		return;

	if (_numberOfActorsInside >= cellparameters.capacity && currentNumberOfChildren < 1 && branchingID < octree->GetMaxBranchingID())
	{
		for (size_t i = 0; i < cellparameters.childrenNumberToSpawn; i++)
		{
			const FVector _subLocation = GetSubLocation(i);
			SubDivideCell(_subLocation);
		}
	}
}

FVector AOctreeCell::GetSubLocation(const int _index)
{
	float _x = 0,
		  _y = 0,
		  _z = 0;

	if (_index < 4)
	{
		_x = _index == 0 || _index == 2 ? box->Bounds.Origin.X + box->Bounds.BoxExtent.X / 2 : box->Bounds.Origin.X - box->Bounds.BoxExtent.X / 2;
		_y = _index == 0 || _index == 1 ? box->Bounds.Origin.Y + box->Bounds.BoxExtent.Y / 2 : box->Bounds.Origin.Y - box->Bounds.BoxExtent.Y / 2;

		_z = box->Bounds.Origin.Z + box->Bounds.BoxExtent.Z / 2;
	}
	else
	{
		_x = _index == 4 || _index == 6 ? box->Bounds.Origin.X + box->Bounds.BoxExtent.X / 2 : box->Bounds.Origin.X - box->Bounds.BoxExtent.X / 2;
		_y = _index == 4 || _index == 5 ? box->Bounds.Origin.Y + box->Bounds.BoxExtent.Y / 2 : box->Bounds.Origin.Y - box->Bounds.BoxExtent.Y / 2;

		_z = box->Bounds.Origin.Z - box->Bounds.BoxExtent.Z / 2;
	}

	return FVector(_x, _y, _z);
}

void AOctreeCell::DrawDebug()
{
	if (!useDebug)
		return;

	DrawDebugBox(GetWorld(), box->Bounds.Origin, box->Bounds.BoxExtent, debugColor, false, -1, 0, debugThickness);
}

