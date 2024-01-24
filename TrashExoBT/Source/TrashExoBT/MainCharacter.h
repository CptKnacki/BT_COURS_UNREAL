// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include <InputMappingContext.h>
#include "MainCharacter.generated.h"

UCLASS()
class TRASHEXOBT_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) TObjectPtr<USpringArmComponent> springArm = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UCameraComponent> camera = nullptr;

	UPROPERTY(EditAnywhere) TSoftObjectPtr<UInputMappingContext> inputContext = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> move = nullptr;
	UPROPERTY(EditAnywhere) TObjectPtr<UInputAction> rotate = nullptr;

public:
	AMainCharacter();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void InitInput();
	void Move(const FInputActionValue& _value);
	void Rotate(const FInputActionValue& _value);
};
