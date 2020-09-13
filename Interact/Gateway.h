// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DesertWalkerGameModeBase.h"
#include "MyPlayerCharacter.h"
#include "Gateway.generated.h"

UCLASS()
class DESERTWALKER_API AGateway : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGateway();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	AMyPlayerCharacter* MyPlayerCharacter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent* CollisionSphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* mStaticMesh;

	UPROPERTY(EditAnywhere, Category ="MyGateNum")
		int RandomGateNum;

	UPROPERTY(EditAnywhere, Category = "MyGateNum")
		bool isStageClear;

	FString tempStr;
	int32 tempMapLevel;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};