// Fill out your copyright notice in the Description page of Project Settings.


#include "Bridge.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
ABridge::ABridge()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->InitSphereRadius(150.0f);
	RootComponent = CollisionSphere;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObj"));
	mStaticMesh->SetupAttachment(RootComponent);

	RandomBridgeNum = 0;
}

// Called when the game starts or when spawned
void ABridge::BeginPlay()
{
	Super::BeginPlay();
	
	MyPlayerCharacter = Cast<AMyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	int temp = MyPlayerCharacter->getNextLevel();

	//if (RandomBridgeNum == temp)
	//{

	//}
	//else
	//{
	//	SetActorHiddenInGame(true);
	//	SetActorEnableCollision(false);
	//	SetActorTickEnabled(false);
	//}

}

// Called every frame
void ABridge::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

