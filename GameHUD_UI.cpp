// Fill out your copyright notice in the Description page of Project Settings.

#include "GameHUD_UI.h"
#include "Controller_StartMenu.h"
#include "GameFramework/PlayerController.h"
#include "MyBasicCharacter.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Containers/UnrealString.h"



void UGameHUD_UI::NativeConstruct()
{
	if (Btn_GameMenu)
	{
		Btn_GameMenu->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_GameMenu_Clicked);
	}

	if (Btn_Inventory)
	{
		Btn_Inventory->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Inventory_Clicked);
	}

	if (Btn_Attack)
	{
		Btn_Attack->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_Attack_Clicked);
	}

	if (Btn_ChangeWeapon)
	{
		Btn_ChangeWeapon->OnClicked.AddDynamic(this, &UGameHUD_UI::Btn_ChangeWeapon_Clicked);
	}
	

}

void UGameHUD_UI::set_HUDbar_value_percent(float const value)
{
	HUD_HPbar_value->SetPercent(value);

	//HUD_HPtext_value = nullptr;
	//const FName TextControlName = FName(TEXT("HUD_HPtext_value"));
	//
	//if (HUD_HPtext_value == nullptr)
	//{
	//	
	//}


}

void UGameHUD_UI::Btn_GameMenu_Clicked()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->ShowGameMenu();
}

void UGameHUD_UI::Btn_Inventory_Clicked()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->ShowInventory();
}


void UGameHUD_UI::Btn_Attack_Clicked()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->WeaponAttack();
}

void UGameHUD_UI::Btn_ChangeWeapon_Clicked()
{
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->ChangeWeapon();
}
