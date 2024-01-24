// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class TRASHEXOBT_API AEnemy : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<USkeletalMeshComponent> skeleton = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<class ACustomAIController> aiController = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<class UDetectionComponent> detection = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<class UAttackComponent> attack = nullptr;

public:
	AEnemy();
	FORCEINLINE TObjectPtr<ACustomAIController> GetAIController() const { return aiController; }
	FORCEINLINE TObjectPtr<UDetectionComponent> GetDetection() const { return detection; }
	FORCEINLINE TObjectPtr<UAttackComponent> GetAttack() const { return attack; }
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void Init();
};
