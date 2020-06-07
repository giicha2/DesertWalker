// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"

// Sets default values
AMyBasicCharacter::AMyBasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDuringAttack = false;

}

float AMyBasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage, 1.0f);
	if (MyHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		if (MyCharacterName == "Player")
		{
			MyHealth -= ActualDamage;
			UE_LOG(LogTemp, Warning, TEXT("Player Character HP : %f"), MyHealth);
		}
		else 
		{
			MyHealth -= ActualDamage;
		}
	}
	return 0.0f;
}

// Called when the game starts or when spawned
void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MyHealth = MyMaxHealth;
}

// Called every frame
void AMyBasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyBasicCharacter::Attack_Melee()
{
}

