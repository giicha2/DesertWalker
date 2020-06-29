// Fill out your copyright notice in the Description page of Project Settings.


#include "DesertWalkerGameModeBase.h"
#include "Blueprint/UserWidget.h"
//#include "HUD_InGame.h"

ADesertWalkerGameModeBase::ADesertWalkerGameModeBase()
{
	//HUDClass = AHUD_InGame::StaticClass();
	//DefaultPawnClass = nullptr;
	//PlayerControllerClass=ADesertWalker
}

void ADesertWalkerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//gameStateEnum = EGameState::GameStart;
	//ChangeUI();
}

void ADesertWalkerGameModeBase::ChangeUI()
{
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
	CurrentWidget->AddToViewport();
}
