// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller_StartMenu.h"
#include "MyBasicCharacter.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "UI_Inventory_Widget.h"
#include "Blueprint/UserWidget.h"
#include "DesertWalkerGameModeBase.h"
#include "MyPlayerCharacter.h"


AController_StartMenu::AController_StartMenu()
{
	isShowGameMenu = false;
	isShowInventory = false;


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

	static ConstructorHelpers::FClassFinder<UUserWidget> InventoryUI(TEXT("/Game/_My/UI/Inventory_WidgetBP"));
	if (InventoryUI.Succeeded())
	{
		uiInventoryBPClass = InventoryUI.Class;

		
	}
	
	static ConstructorHelpers::FClassFinder<UUserWidget> ItmeSlot(TEXT("/Game/_My/UI/ItemSlot_BP"));
	if (ItmeSlot.Succeeded())
	{
		uiItemSlotBPClass = ItmeSlot.Class;
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> DieUI(TEXT("/Game/_My/UI/DieUI_BP"));
	if (DieUI.Succeeded())
	{
		uiGameDieBPClass = DieUI.Class;
	}
}

void AController_StartMenu::SetupInputComponent()
{
	APlayerController::SetupInputComponent();

	InputComponent->BindAction("ShowGameMenu", IE_Pressed, this, &AController_StartMenu::ShowGameMenu);
	InputComponent->BindAction("ShowInventory", IE_Pressed, this, &AController_StartMenu::ShowInventory);
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
		}
		isShowGameMenu = true;
	}
}

void AController_StartMenu::CloseGameMenu()
{
	uiGameMenuWidget->RemoveFromViewport();
	isShowGameMenu = false;
}


void AController_StartMenu::ShowInventory()
{
	if (uiInventoryBPClass && isShowInventory == false)
	{
		AMyPlayerCharacter* MyPlayerCharacter = Cast<AMyPlayerCharacter>(GetOwner());

		uiInventoryWidget = CreateWidget<UUserWidget>(GetWorld(), uiInventoryBPClass);
		if (uiInventoryWidget)
		{
			//uiInventoryWidget->AddToViewport();
			//CreateItemSlots();


		}
		isShowInventory = true;
	}


}

void AController_StartMenu::CreateItemSlots()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;


	//Show ItemSlots
	//UUI_Inventory_Widget* MyInvenWidgetClass = Cast<UUI_Inventory_Widget>(GetWorld());
	//
	//UUI_Inventory_Widget* MyInvenPanel = Cast<UUI_Inventory_Widget>(GetWorld());
	//auto s = MyInvenPanel->GridPanel_ItemSlots;
	//
	//for (int i = 0; i < 8; i++)
	//{
	//	//MyInvenWidgetClass->GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	s->AddChildToGrid(uiItemSlotWidget);
	//	//uiItemSlotWidget->AddToViewport();
	//	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, __FUNCTION__);
	//}
}

void AController_StartMenu::CloseInventory()
{
	uiInventoryWidget->RemoveFromViewport();
	isShowInventory = false;
}


void AController_StartMenu::WeaponAttack()
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	MyCharac->WeaponAttack();
}

void AController_StartMenu::ChangeWeapon()
{
	AMyBasicCharacter* MyCharac = Cast<AMyBasicCharacter>(GetPawn());
	MyCharac->OnChangeWeapon();
}

void AController_StartMenu::ShowDieUI()
{
	if (uiGameDieBPClass)
	{
		uiGameDieWidget = CreateWidget<UUserWidget>(GetWorld(), uiGameDieBPClass);
		if (uiGameDieWidget)
		{
			uiGameWidget->RemoveFromParent();
			uiGameDieWidget->AddToViewport();
			
			bShowMouseCursor = true;
			bEnableClickEvents = true;
			bEnableMouseOverEvents = true;
		}
	}
}
