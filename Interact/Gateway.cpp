// Fill out your copyright notice in the Description page of Project Settings.


#include "Gateway.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"



// Sets default values
AGateway::AGateway()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("GateCollisionSphere"));
	CollisionSphere->InitSphereRadius(150.0f);
	RootComponent = CollisionSphere;

	mStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshObj"));
	mStaticMesh->SetupAttachment(RootComponent);

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AGateway::OnOverlapBegin);
	
	

	RandomGateNum = 0;
	tempStr = NULL;
	


}

// Called when the game starts or when spawned
void AGateway::BeginPlay()
{
	Super::BeginPlay();
	
	MyPlayerCharacter = Cast<AMyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	tempMapLevel = MyPlayerCharacter->getNextLevel();

	tempStr = "/Game/Level0" + FString::FromInt(RandomGateNum);



	/*if (RandomGateNum == tempMapLevel)
	{
		
	}
	else
	{
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
		SetActorTickEnabled(false);
	}*/
}

// Called every frame
void AGateway::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGateway::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
	if (isStageClear)
	{
		UGameplayStatics::OpenLevel(GetWorld(), "/Game/Level01");

		int tmp = 1;
		MyPlayerCharacter->setNextLevel(tmp);
	}
	else
	{
		if (OtherActor->IsA(AMyPlayerCharacter::StaticClass()))
		{
			UGameplayStatics::OpenLevel(GetWorld(), *tempStr);

			int tmp = RandomGateNum;
			MyPlayerCharacter->setNextLevel(tmp);
		}
		else
		{

		}
	}

	
}

