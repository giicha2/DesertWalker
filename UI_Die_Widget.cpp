// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Die_Widget.h"
#include "Kismet/GameplayStatics.h"

void UUI_Die_Widget::NativeConstruct()
{
	if (Btn_GotoLobby)
	{
		Btn_GotoLobby->OnClicked.AddDynamic(this, &UUI_Die_Widget::GotoLobby);
	}

	if (Btn_StartNewGame)
	{
		Btn_StartNewGame->OnClicked.AddDynamic(this, &UUI_Die_Widget::StartNewGame);
	}

}

void UUI_Die_Widget::GotoLobby()
{
	UGameplayStatics::OpenLevel(this, "/Game/StartMenu_Level");
}

void UUI_Die_Widget::StartNewGame()
{
	UGameplayStatics::OpenLevel(this, "/Game/Level01");
}
