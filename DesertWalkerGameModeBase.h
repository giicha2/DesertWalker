// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DesertWalkerGameModeBase.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EGameState :uint8
{
	GameStart,
	GamePlay,
	GamePause,
	GameOver,
};

UCLASS()
class DESERTWALKER_API ADesertWalkerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	ADesertWalkerGameModeBase();

	virtual void BeginPlay()override;

	UPROPERTY(EditAnywhere, Category = "UMG Game")
		EGameState gameStateEnum;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG Game")
		TSubclassOf<UUserWidget>HUDWidgetClass;

	UUserWidget* CurrentWidget;

public:
	//void ChangeUI();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myCharacterName_Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myCharacterLevel_Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myCharacterExp_Text;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString myCharacterScore_Text;

};
