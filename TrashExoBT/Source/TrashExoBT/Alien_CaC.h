// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Alien_CaC.generated.h"

UCLASS()
class TRASHEXOBT_API AAlien_CaC : public APawn
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<USkeletalMeshComponent> mesh = nullptr;

	UPROPERTY(EditAnywhere) float range = 700;
	UPROPERTY(EditAnywhere) TArray<TEnumAsByte<EObjectTypeQuery>> hitLayers;

	UPROPERTY(EditAnywhere) TObjectPtr<AActor> target = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess)) bool bHasTargetInSight = false;
	UPROPERTY(EditAnywhere) FName boolKeyName = "bHasTargetInSight";
	UPROPERTY(EditAnywhere) FName vectorKeyName = "targetLocation";
	UPROPERTY() TObjectPtr<class ACustomAIController> aiController = nullptr;

public:
	AAlien_CaC();
	FORCEINLINE TObjectPtr<class ACustomAIController> GetAIController() const { return aiController; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void DetectPlayer();
	void Init();
	void DrawDebug();
	void UpdateBehaviourTree();
};
