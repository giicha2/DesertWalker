// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Controller_StartMenu.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API AController_StartMenu : public APlayerController
{
	GENERATED_BODY()
		AController_StartMenu();

protected:
	void SetupInputComponent()override;

public:
	void ShowGameMenu();
	void CloseGameMenu();
	void WeaponAttack();
	void ChangeWeapon();

	bool isShowGameMenu;
private:
	TSubclassOf<class UUserWidget>uiGameBPClass;
	UUserWidget* uiGameWidget;

	TSubclassOf<class UUserWidget>uiGameMenuBPClass;
	UUserWidget* uiGameMenuWidget;
};
