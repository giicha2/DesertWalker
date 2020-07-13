// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBasicCharacter.h"
#include "PlayerWeapon_Melee.h"
#include "Engine/World.h"
#include "Engine.h"
#include "AIController.h"
#include "Components/WidgetComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"
#include "HPBar.h"
#include "GameHUD_UI.h"


// Sets default values
AMyBasicCharacter::AMyBasicCharacter():
	MyHealth(MyMaxHealth),
	Widget_Component(CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthValue")))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	isDeath = false;
	isDuringAttack = false;

	//make HPbar on the head
	if (Widget_Component)
	{
		Widget_Component->SetupAttachment(RootComponent);
		Widget_Component->SetWidgetSpace(EWidgetSpace::Screen);
		Widget_Component->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
		static ConstructorHelpers::FClassFinder<UUserWidget>widget_class(TEXT("/Game/_My/UI/HPbar_BP"));
		
		if (widget_class.Succeeded())
		{
			//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Magenta, __FUNCTION__);
			Widget_Component->SetWidgetClass(widget_class.Class);
			
		}
	}
}

// Called when the game starts or when spawned
void AMyBasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	

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

	//make HPbar on the character head
	auto const uw = Cast<UHPBar>(Widget_Component->GetUserWidgetObject());
	auto const gameHUD_hpBar = Cast<UGameHUD_UI>(Widget_Component->GetUserWidgetObject());
	float tempNum = MyHealth / MyMaxHealth;
	if (MyCharacterName == "Player")
	{
		if (gameHUD_hpBar)
		{
			gameHUD_hpBar->set_HUDbar_value_percent(tempNum);
		}
	}
	else
	{
		if (uw)
		{
			uw->set_bar_value_percent(tempNum);
		}
	}



}

// Called to bind functionality to input
void AMyBasicCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



float AMyBasicCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	PlayAnimMontage(BeHit_AnimMontage,1.0f);
	if (MyHealth <= 0.0f)
	{
		return 0.0f;
	}
	const float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (ActualDamage > 0.0f)
	{
		MyHealth -= ActualDamage;	
	}

	if (MyHealth <= 0.0f)
	{

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
	
	//UAnimMontage* pAnimMtg = GetMesh()->GetAnimInstance()->PlaySlotAnimationAsDynamicMontage(BeHit_AnimMontage, TEXT("FullBodySlot"), 0.3f, 0.3f, 1.0f);
	//PlayAnimMontage(pAnimMtg, 1.0f);

	float BeHitAimDuration=PlayAnimMontage(BeHit_AnimMontage);

	if (DamageTaken > 0.0f)
	{
		ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);	
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT(" HP : %f"), MyHealth));
	}
}

void AMyBasicCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	isDeath = true;

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

	if (Controller)
	{
		Controller->Destroy();
	}


	GetMesh()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetSimulatePhysics(true);

	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, "DieFunc!!!");

	float DeathAnimDuration = PlayAnimMontage(Death_AnimMontage);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AMyBasicCharacter::OnDieAnimationEnd, DeathAnimDuration,false);
}
void AMyBasicCharacter::OnDieAnimationEnd()
{
	this->SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

float AMyBasicCharacter::get_Health() const
{
	return MyHealth;
}

float AMyBasicCharacter::get_maxHealth() const
{
	return MyMaxHealth;
}

void AMyBasicCharacter::set_health(float const new_health)
{
	MyHealth = new_health;
}