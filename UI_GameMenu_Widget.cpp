// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_GameMenu_Widget.h"
#include "Controller_StartMenu.h"

void UUI_GameMenu_Widget::NativeConstruct()
{
	if (Btn_GameMenu_Close)
	{
		Btn_GameMenu_Close->OnClicked.AddDynamic(this, &UUI_GameMenu_Widget::Btn_GameMenu_CloseWindow);
	}


}

void UUI_GameMenu_Widget::Btn_GameMenu_CloseWindow()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->CloseGameMenu();
}

