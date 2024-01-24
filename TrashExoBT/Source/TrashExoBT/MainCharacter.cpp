// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include <EnhancedInputComponent.h>
#include <EnhancedInputSubsystems.h>
#include <Kismet/KismetMathLibrary.h>

// Sets default values
AMainCharacter::AMainCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	springArm = CreateDefaultSubobject<USpringArmComponent>("springArm");
	camera = CreateDefaultSubobject<UCameraComponent>("camera");

	springArm->SetupAttachment(RootComponent);
	camera->SetupAttachment(springArm);
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	InitInput();

	UEnhancedInputComponent* _input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	_input->BindAction(move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
	_input->BindAction(rotate, ETriggerEvent::Triggered, this, &AMainCharacter::Rotate);
}

void AMainCharacter::InitInput()
{
	APlayerController* _p = GetWorld()->GetFirstPlayerController();

	UEnhancedInputLocalPlayerSubsystem* _inputSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(_p->GetLocalPlayer());
	_inputSystem->ClearAllMappings();
	_inputSystem->AddMappingContext(inputContext.LoadSynchronous(), 0);
}

void AMainCharacter::Move(const FInputActionValue& _value)
{
	FVector2D _axis2D = _value.Get<FVector2D>();


	FVector _movement = springArm->GetForwardVector() * _axis2D.Y + springArm->GetRightVector() * _axis2D.X;

	AddMovementInput(_movement);

	if (_axis2D.X != 0 || _axis2D.Y != 0)
	{
		FRotator _rotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), GetActorLocation() + _movement);
		_rotation.Pitch = 0;
		_rotation.Roll = 0;
		_rotation.Yaw -= 90;

		GetComponentByClass<USkeletalMeshComponent>()->SetWorldRotation(_rotation);
	}
}

void AMainCharacter::Rotate(const FInputActionValue& _value)
{
	float _axis = _value.Get<float>();

	FRotator _rotation = springArm->GetComponentRotation();
	_rotation.Yaw += _axis;

	springArm->SetWorldRotation(_rotation);
}

