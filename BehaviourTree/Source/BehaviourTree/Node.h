// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Node.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREE_API UNodeNav : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<class AGridNav> grid = nullptr;
	UPROPERTY(EditAnywhere) FVector position;
	UPROPERTY(EditAnywhere) TArray<int> successors = {};

public:
	FORCEINLINE TArray<int> GetSuccessors() const { return successors; }
	FORCEINLINE FVector GetPosition() const { return position; }
	void InitNode(TObjectPtr<AGridNav> _grid, FVector _position);
	void AddSuccessor(int _successor);
	void DrawDebug(FColor _nodeColor, FColor _lineColor);


	
};
