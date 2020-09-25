// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPC_Shop.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Controller_StartMenu.h"

// Sets default values
AMyNPC_Shop::AMyNPC_Shop()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->InitSphereRadius(250.0f);
	RootComponent = CollisionSphere;

	mSkeltalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShopNPC_Obj"));
	mSkeltalMesh->SetupAttachment(RootComponent);

	//CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGateway::OnOverlapBegin);



}

// Called when the game starts or when spawned
void AMyNPC_Shop::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyNPC_Shop::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyNPC_Shop::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

