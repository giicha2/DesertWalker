// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_UI.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UStartMenu_UI::NativeConstruct()
{
	if (Btn_StartGame)
	{
		Btn_StartGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Btn_StartGame_Clicked);
	}

	if (Btn_ExitGame)
	{
		Btn_ExitGame->OnClicked.AddDynamic(this, &UStartMenu_UI::Btn_ExitGame_Clicked);
	}
}


void UStartMenu_UI::Btn_StartGame_Clicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), "/Game/Level01");
}

void UStartMenu_UI::Btn_ExitGame_Clicked()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}
