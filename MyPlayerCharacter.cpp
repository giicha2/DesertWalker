// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/DefaultPawn.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Engine.h"
#include "PlayerWeapon_Melee.h"

AMyPlayerCharacter::AMyPlayerCharacter()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 1000.f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;

	isDuringAttack = false;
	ComboAttack_Num = 0;
}

void AMyPlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	SpawnDefaultInventory();
}

void AMyPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &AMyBasicCharacter::WeaponAttack);
	PlayerInputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &AMyBasicCharacter::OnChangeWeapon);
}

void AMyPlayerCharacter::MoveForward(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !(isDuringAttack))
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, value);
	}
}

void AMyPlayerCharacter::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f) && !(isDuringAttack))
	{
		const FRotator Rot = Controller->GetControlRotation();
		const FRotator YawRot(0, Rot.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRot).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}

}


void AMyPlayerCharacter::Attack_Melee()
{
	if (!isDuringAttack)
	{
		if (ComboAttack_Num < 3)
		{
			int tmp_Num = rand() % 3 + 1;
			FString PlaySection = "Attack_" + FString::FromInt(tmp_Num);
			PlayAnimMontage(Attack_AnimMontage, 1.0f, FName(*PlaySection));
			ComboAttack_Num++;
			isDuringAttack = true;
		
		}
		else
		{
			PlayAnimMontage(Attack_AnimMontage, 1.0f, FName("Attack_4"));
			ComboAttack_Num = 0;
		}
	}
}

void AMyPlayerCharacter::Attack_Melee_End()
{
	isDuringAttack = false;
}
