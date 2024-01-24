// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridNav.generated.h"

UCLASS()
class BEHAVIOURTREE_API AGridNav : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) int size = 4;
	UPROPERTY(EditAnywhere) int gap = 200;
	UPROPERTY(EditAnywhere) FColor nodeColor = FColor::Red;
	UPROPERTY(EditAnywhere) FColor linesColor = FColor::Green;
	UPROPERTY(EditAnywhere, meta = (EditInLine)) TArray<class UNodeNav*> nodes = {};


public:	
	AGridNav();
	FORCEINLINE TArray<class UNodeNav*> GetNodes() const { return nodes; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(CallInEditor) void Generate();
	void SetSuccessors();
	void DrawDebug();

};
