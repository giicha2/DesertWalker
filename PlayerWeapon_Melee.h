// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyBasicCharacter.h"
#include "MyPlayerCharacter.h"
#include "PlayerWeapon_Melee.generated.h"

UCLASS()
class DESERTWALKER_API APlayerWeapon_Melee : public AActor
{
	GENERATED_BODY()
private:
	UPROPERTY(VisibleDefaultsOnly, Category = Weapon)
		USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		class UBoxComponent* WeaponCollision;

	bool isNowAttack;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Sets default values for this actor's properties
	APlayerWeapon_Melee(const class FObjectInitializer& ObjectInitializer);

	void SetOwningPawn(AMyBasicCharacter* NewOwner);
	void AttachMeshToPawn();
	void OnEquip(const APlayerWeapon_Melee* LastWeapon);
	void OnUnEquip();
	void StartAttack();
	void StopAttack();

	//virtual void NotifyActorBeginOverlap(AActor* OtherActor)override;


protected:
	class AMyBasicCharacter* MyPawn;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
		UAnimMontage* AttackAnim;


};

