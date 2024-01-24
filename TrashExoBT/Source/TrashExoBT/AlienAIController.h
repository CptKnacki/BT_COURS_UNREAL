// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DetectionComponent.h"
#include "AlienAIController.generated.h"

/**
 * 
 */
UCLASS()
class TRASHEXOBT_API ACustomAIController : public AAIController
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere) TObjectPtr<UDetectionComponent> detectionComponent = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<APawn> controlledPawn = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UBehaviorTree> tree = nullptr;
	UPROPERTY(EditAnywhere) FName patrolLocKeyName = "patrolLocation";
	UPROPERTY(EditAnywhere) FName keyDetected = "targetDetected";
	UPROPERTY(EditAnywhere) FName keyTarget = "target";
	UPROPERTY(EditAnywhere) FName keyIsInRange = "isInRange";

public:
	FORCEINLINE TObjectPtr<APawn> GetControlledPawn() const { return controlledPawn; }
	FORCEINLINE FName GetKeyTarget() const { return keyTarget; }
	FORCEINLINE FName GetKeyDetected() const { return keyDetected; }
	FORCEINLINE FName GetKeyIsInRange() const { return keyIsInRange; }
	ACustomAIController();

	UFUNCTION() void ReceiveTarget(AActor* _target);
	UFUNCTION() void ReceiveTargetDetected(bool _value);
	UFUNCTION() void ReceiveIsInRange(bool _value);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Init();
	void Debug();
};
