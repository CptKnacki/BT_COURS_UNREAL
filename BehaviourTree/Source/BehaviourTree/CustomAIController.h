// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CustomAIController.generated.h"

/**
 * 
 */
UCLASS()
class BEHAVIOURTREE_API ACustomAIController : public AAIController
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<UBehaviorTree> tree = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<APawn> controlledPawn = nullptr;

public:
	FORCEINLINE TObjectPtr<APawn> GetControlledPawn() const { return controlledPawn; }
	ACustomAIController();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Init();
};
