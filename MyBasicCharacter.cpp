// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"
#include "PlayerWeapon_Melee.h"
#include "Engine/World.h"
#include "Engine.h"

// Sets default values
AMyBasicCharacter::AMyBasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	isDuringAttack = false;



}

// Called when the game starts or when spawned
void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	MyHealth = MyMaxHealth;
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, MyCharacterName.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT(" HP : %f"), MyHealth));
}


//==================================================================================
//==============Change Weapon=======================================================
USkeletalMeshComponent* AMyBasicCharacter::GetSpecificPawnMesh() const
{
	return GetMesh();
}

FName AMyBasicCharacter::GetWeaponAttachPoint() const
{
	return WeaponAttachPoint;
}

void AMyBasicCharacter::AddWeapon(APlayerWeapon_Melee* Weapon)
{
	if (Weapon)
	{
		Inventory.AddUnique(Weapon);
	}
}

void AMyBasicCharacter::SetCurrentWeapon(APlayerWeapon_Melee* NewWeapon, APlayerWeapon_Melee* LastWeapon)
{
	APlayerWeapon_Melee* LocalLastWeapon = NULL;

	if (LastWeapon != NULL)
	{
		LocalLastWeapon = LastWeapon;
	}
	else if (NewWeapon != CurrentWeapon)
	{
		LocalLastWeapon = CurrentWeapon;
	}

	if (LocalLastWeapon)
	{
		LocalLastWeapon->OnUnEquip();
	}

	CurrentWeapon = NewWeapon;

	if (NewWeapon)
	{
		NewWeapon->SetOwningPawn(this);
		NewWeapon->OnEquip(LastWeapon);
	}
}

void AMyBasicCharacter::EquipWeapon(APlayerWeapon_Melee* Weapon)
{
	if (Weapon)
	{
		SetCurrentWeapon(Weapon, CurrentWeapon);
	}
}

void AMyBasicCharacter::SpawnDefaultInventory()
{
	int32 NumWeaponClasses = DefaultInventoryClasses.Num();

	for (int32 i = 0; i < NumWeaponClasses; i++)
	{
		if (DefaultInventoryClasses[i])
		{
			FActorSpawnParameters SpawnInfo;

			UWorld* WRLD = GetWorld();
			APlayerWeapon_Melee* NewWeapon = WRLD->SpawnActor<APlayerWeapon_Melee>(DefaultInventoryClasses[i], SpawnInfo);
			AddWeapon(NewWeapon);
		}
	}

	if (Inventory.Num() > 0)
	{
		EquipWeapon(Inventory[0]);
	}
}

void AMyBasicCharacter::OnChangeWeapon()
{
	const int32 CurrentWeaponIndex = Inventory.IndexOfByKey(CurrentWeapon);

	APlayerWeapon_Melee* NextWeapon = Inventory[(CurrentWeaponIndex + 1) % Inventory.Num()];

	EquipWeapon(NextWeapon);
}

void AMyBasicCharacter::WeaponAttack()
{
	CurrentWeapon->StartAttack();
}
//------------------------------------------------------------------------------------



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



float AMyBasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{

	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		MyHealth -= ActualDamage;
		//if(MyCharacterName=="Player")
		//{
		//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("Player HP : %f"), MyHealth));
		//}
		//else
		//{
		//	
		//}
				
	}

	if (MyHealth <= 0)
	{
		PlayAnimMontage(Death_AnimMontage, 1.0f);
		Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
	}
	else
	{
		OnHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
	}
	return ActualDamage;
}

void AMyBasicCharacter::OnHit(float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser)
{
	float BeHitAimDuration=PlayAnimMontage(BeHit_AnimMontage);

	if (DamageTaken > 0.0f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);	
	}
	
}

void AMyBasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	MyHealth = FMath::Min(0.0f, MyHealth);

	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? Cast<const UDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject()) : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);

	GetWorldTimerManager().ClearAllTimersForObject(this);

	if (GetCapsuleComponent())
	{
		GetCapsuleComponent()->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_Pawn, ECR_Ignore);
		GetCapsuleComponent()->BodyInstance.SetResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
	}

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->StopMovementImmediately();
		GetCharacterMovement()->DisableMovement();
	}

	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyBasicCharacter::OnDieAnimationEnd, DeathAnimDuration,false);
}
void AMyBasicCharacter::OnDieAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}
//UE_LOG(LogTemp, Warning, TEXT("Player Character HP : %f"), MyHealth);
