// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Octree.generated.h"

UCLASS()
class BEHAVIOURTREE_API AOctree : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TObjectPtr<class AOctreeCell> root = nullptr;
	UPROPERTY(EditAnywhere) TSubclassOf<AOctreeCell> cellToSpawn = nullptr;
	UPROPERTY(EditAnywhere) int maxBranchingID = 4;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite) TObjectPtr<AActor> navMeshBoundsVolume = nullptr;

public:	
	AOctree();
	FORCEINLINE TSubclassOf<AOctreeCell> GetOctreeCellToSpawn() const { return cellToSpawn; }
	FORCEINLINE int GetMaxBranchingID() const { return maxBranchingID; }

	UFUNCTION(CallInEditor) void GenerateOctree();
	UFUNCTION(CallInEditor) void DestroyOctree();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void InitRootCell();
};
