// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "MyBasicCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"

AController_StartMenu::AController_StartMenu()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> obj(TEXT("/Game/_My/UI/HUD_BP"));
	if (obj.Succeeded())
	{
		uiGameBPClass = obj.Class;
	}

	if (uiGameBPClass)
	{
		uiGameWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameBPClass);
		if (uiGameWidget)
		{
			uiGameWidget->AddToViewport();
		}
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> gamemenuUI(TEXT("/Game/_My/UI/GameMenu_BP"));
	if (gamemenuUI.Succeeded())
	{
		uiGameMenuBPClass = gamemenuUI.Class;
	}

	isShowGameMenu = false;
}

void AController_StartMenu::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AController_StartMenu::ShowGameMenu);
	InputComponent->BindAction("Attack", IE_Pressed, this, &AController_StartMenu::WeaponAttack);
	InputComponent->BindAction("ChangeWeapon", IE_Pressed, this, &AController_StartMenu::ChangeWeapon);
}

void AController_StartMenu::ShowGameMenu()
{
	if (uiGameMenuBPClass&& isShowGameMenu==false)
	{
		uiGameMenuWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameMenuBPClass);
		if (uiGameMenuWidget)
		{
			uiGameMenuWidget->AddToViewport();
			//isShowGameMenu = true;
		}
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
}

void AController_StartMenu::CloseGameMenu()
{
	uiGameMenuWidget->RemoveFromViewport();
	isShowGameMenu = false;
}

void AController_StartMenu::WeaponAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	MyCharac->WeaponAttack();
}

void AController_StartMenu::ChangeWeapon()
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	MyCharac->OnChangeWeapon();
}
