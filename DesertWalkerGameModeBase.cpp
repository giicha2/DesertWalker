// Fill out your copyright notice in the Description page of Project Settings.


#include "DesertWalkerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD_HUD.h"
#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"

ADesertWalkerGameModeBase::ADesertWalkerGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> player(TEXT("/Game/_My/Mesh/MyPlayerCharacter_BP"));
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}

	HUDClass = AGameHUD_HUD::StaticClass();
	PlayerControllerClass = AController_StartMenu::StaticClass();
}

void ADesertWalkerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//ChangeUI();
}

//void ADesertWalkerGameModeBase::ChangeUI()
//{
//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
//	CurrentWidget->AddToViewport();
//}
