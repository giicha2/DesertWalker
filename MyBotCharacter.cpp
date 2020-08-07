// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBotCharacter.h"
#include "MyBasicCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MyProjectile.h"
#include "Engine/World.h"
#include "MyPlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Engine.h"

AMyBotCharacter::AMyBotCharacter()
{
	WeaponCollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("WeaponCollisionSphere"));
	WeaponCollisionSphere->InitSphereRadius(20.0f);
	WeaponCollisionSphere->AttachTo(GetMesh(), "WeaponPoint");

	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AMyBotCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	if (OtherActor->IsA(AActor::StaticClass()) && PlayAnimMontage(montage) > 0.2f)
	{
		UGameplayStatics::ApplyDamage(OtherActor, 10.0f, NULL, this, UDamageType::StaticClass());

	}
}

int AMyBotCharacter::melee_attack_Implementation()
{
	if (montage)
	{
		PlayAnimMontage(montage);

		if (MyCharacterName == "Range" && MyBullet)
		{
			const FRotator SpawnRotation = GetActorRotation();
			const FVector SpawnLocation = GetActorLocation() + SpawnRotation.RotateVector(FVector(80.0f, 30.0f, 10.0f));
			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				World->SpawnActor<AMyProjectile>(MyBullet, SpawnLocation, SpawnRotation);
			}
		}
	}
	return 0;
}

UAnimMontage* AMyBotCharacter::get_montage() const
{
	return montage;
}


