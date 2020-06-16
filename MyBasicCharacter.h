// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyBasicCharacter.generated.h"

UCLASS()
class DESERTWALKER_API AMyBasicCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyBasicCharacter();


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		FName MyCharacterName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = MyState)
		float MyMaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = MyState)
		float MyHealth;

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;


	//=============================================================
	//=====change Weapon==========================================
	USkeletalMeshComponent* GetSpecificPawnMesh() const;

	FName GetWeaponAttachPoint()const;

	void EquipWeapon(class APlayerWeapon_Melee* Weapon);

	void OnChangeWeapon();

	void WeaponAttack();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		FName WeaponAttachPoint;

	TArray<class APlayerWeapon_Melee*>Inventory;

	class APlayerWeapon_Melee* CurrentWeapon;

	void AddWeapon(class APlayerWeapon_Melee* Weapon);

	void SetCurrentWeapon(class APlayerWeapon_Melee* NewWeapon, class APlayerWeapon_Melee* LastWeapon);

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
		TArray<TSubclassOf<class APlayerWeapon_Melee>>DefaultInventoryClasses;

	void SpawnDefaultInventory();
	//--------------------------------------------------------------------------

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser);

	virtual void Die(float KillingDamage, struct FDamageEvent const& DamageEvent, AController* Killer,AActor* DamageCauser);

	void OnDieAnimationEnd();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Attack_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* BeHit_AnimMontage;

	UPROPERTY(EditDefaultsOnly, Category = Pawn)
		UAnimMontage* Death_AnimMontage;



	bool isDuringAttack = true;
	int32 ComboAttack_Num;

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* GetHitFX;

	UPROPERTY(EditDefaultsOnly, Category = "MyFX")
		UParticleSystem* DieFX;


};
