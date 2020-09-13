// Fill out your copyright notice in the Description page of Project Settings.


#include "DesertWalkerGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "GameHUD_HUD.h"
#include "Controller_StartMenu.h"
#include "UObject/ConstructorHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Engine.h"
#include "MyPlayerCharacter.h"

ADesertWalkerGameModeBase::ADesertWalkerGameModeBase()
{
	static ConstructorHelpers::FClassFinder<APawn> player(TEXT("/Game/_My/Mesh/MyPlayerCharacter_BP"));
	if (player.Succeeded())
	{
		DefaultPawnClass = player.Class;
	}

	HUDClass = AGameHUD_HUD::StaticClass();
	PlayerControllerClass = AController_StartMenu::StaticClass();

	myCharacterName_Text = "Name : Desert Walker";
	myCharacterLevel_Text = "Level : 10";


}

void ADesertWalkerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//AMyPlayerCharacter* MyPlayerCharacter = Cast<AMyPlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	//int temp = MyPlayerCharacter->getNextLevel();


}

//void ADesertWalkerGameModeBase::ChangeUI()
//{
//	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(),HUDWidgetClass);
//	CurrentWidget->AddToViewport();
//}
