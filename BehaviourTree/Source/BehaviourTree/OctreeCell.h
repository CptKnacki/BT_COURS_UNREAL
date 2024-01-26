// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/BoxComponent.h>
#include "OctreeCell.generated.h"

USTRUCT()
struct FOctreCellParameter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) int childrenNumberToSpawn = 8;
	UPROPERTY(EditAnywhere) int capacity = 0;
};


UCLASS()
class BEHAVIOURTREE_API AOctreeCell : public AActor
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNumberOfActorsInsideUpdate, int, _numberOfActorsInside);

	UPROPERTY(BlueprintCallable, BlueprintAssignable) FOnNumberOfActorsInsideUpdate onNumberOfActorsInsideUpdate;

	
	UPROPERTY(EditAnywhere) TObjectPtr<class AOctree> octree = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<AOctreeCell> parent = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBoxComponent> box = nullptr;
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<AOctreeCell>> cellChildren = {};
	UPROPERTY(EditAnywhere) TArray<TObjectPtr<AActor>> actorsInSight = {};
	UPROPERTY(EditAnywhere) FOctreCellParameter cellparameters;
	UPROPERTY(EditAnywhere) bool isActive = true;
	UPROPERTY(EditAnywhere) int currentActorsInside = 0;
	UPROPERTY(EditAnywhere) int currentNumberOfChildren = 0;
	UPROPERTY(EditAnywhere) int branchingID = 1;
	UPROPERTY(EditAnywhere) TArray<TSubclassOf<AActor>> classToDetect;

	UPROPERTY(EditAnywhere) bool useDebug = true;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "useDebug", EditConditionHides)) bool debugArea = true;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "useDebug", EditConditionHides)) int debugThickness = 0;
	UPROPERTY(EditAnywhere, meta = (EditCondition = "useDebug", EditConditionHides)) FColor debugColor = FColor::Blue;

public:	
	AOctreeCell();
	FORCEINLINE void SetOctree(TObjectPtr<AOctree> _octree) { octree = _octree; }
	FORCEINLINE FOnNumberOfActorsInsideUpdate& OnNumberOfActorsInsideUpdate() { return onNumberOfActorsInsideUpdate; }
	UFUNCTION() void SetCellDimensions(const double _length, const double _width, const double _height);
	UFUNCTION() void SetCellDimension(const FVector& _dimensions);
	UFUNCTION() void ManageCellBehvaiour(const int _numberOfActorsInside);
	FVector GetSubLocation(const int _index);
	void CustomDestroy();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	virtual void NotifyActorBeginOverlap(AActor* _otherActor) override;
	virtual void NotifyActorEndOverlap(AActor* _otherActor) override;
	void InitSubCell(const int _branchingID, AOctree* _octree, AOctreeCell* _parent);
	void SubDivideCell(const FVector _subLocation);
	void RemoveSubCells();
	void DrawDebug();
};
