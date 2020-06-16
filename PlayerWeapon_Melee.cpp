// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerWeapon_Melee.h"
#include "Components/BoxComponent.h"
#include "Engine.h"
#include "Engine/EngineTypes.h"
#include "MyBotCharacter.h"




// Sets default values
APlayerWeapon_Melee::APlayerWeapon_Melee(const class FObjectInitializer& ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WeaponMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("WeaponMesh"));
	WeaponMesh->CastShadow = true;
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = WeaponMesh;

	WeaponCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("WeaponCollsion"));
	WeaponCollision->SetBoxExtent(FVector(5.0f, 5.0f, 5.0f));
	WeaponCollision->AttachTo(WeaponMesh, "HandWeaponSocket");

	isNowAttack = false;


	WeaponCollision->OnComponentBeginOverlap.AddDynamic(this, &APlayerWeapon_Melee::OnBeginOverlap);
}

//===============================================================================
//====================Change Weapon=============================================

void APlayerWeapon_Melee::SetOwningPawn(AMyBasicCharacter* NewOwner)
{
	if (MyPawn != NewOwner)
	{
		MyPawn = NewOwner;
	}
}

void APlayerWeapon_Melee::OnEquip(const APlayerWeapon_Melee* LastWeapon)
{
	AttachMeshToPawn();
	WeaponMesh->SetHiddenInGame(false);
}

void APlayerWeapon_Melee::OnUnEquip()
{
	WeaponMesh->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	WeaponMesh->SetHiddenInGame(true);
}

void APlayerWeapon_Melee::AttachMeshToPawn()
{
	if (MyPawn)
	{
		USkeletalMeshComponent* PawnMesh = MyPawn->GetSpecificPawnMesh();
		FName AttachPoint = MyPawn->GetWeaponAttachPoint();
		WeaponMesh->AttachTo(PawnMesh, AttachPoint);
	}
}
//---------------------------------------------------------


void APlayerWeapon_Melee::StartAttack()
{
	float AttackAnimDuration = MyPawn->PlayAnimMontage(MyPawn->Attack_AnimMontage);

	isNowAttack = true;

	FTimerHandle TimerHandle_StopAttack;
	GetWorldTimerManager().SetTimer(TimerHandle_StopAttack, this, &APlayerWeapon_Melee::StopAttack, AttackAnimDuration, false);
}

void APlayerWeapon_Melee::StopAttack()
{
	MyPawn->StopAnimMontage(MyPawn->Attack_AnimMontage);
	isNowAttack = false;
}

//void APlayerWeapon_Melee::NotifyActorBeginOverlap(AActor* OtherActor)
//{
//	Super::NotifyActorBeginOverlap(OtherActor);
//
//	AMyBotCharacter* MyBot = Cast<AMyBotCharacter>(OtherActor);
//
//	if (OtherActor->IsA(AActor::StaticClass()) && isNowAttack == true && OtherActor==MyBot)
//	{
//		UGameplayStatics::ApplyDamage(OtherActor, 50.0f, NULL, this, UDamageType::StaticClass());
//		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
//	}
//}



void APlayerWeapon_Melee::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AMyBotCharacter* MyBot = Cast<AMyBotCharacter>(OtherActor);

	if (OtherActor->IsA(AActor::StaticClass()) && isNowAttack == true && OtherActor == MyBot)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
		UGameplayStatics::ApplyDamage(OtherActor, 50.0f, NULL, this, UDamageType::StaticClass());
		//UGameplayStatics::ApplyDamage(OtherActor, 50.0f, NULL, GetOwner(), NULL);
	}
	/*if (OtherActor == this && OtherActor == GetOwner())
	{		
		return;
	}*/	
}