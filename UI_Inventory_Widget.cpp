// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"
#include "Controller_StartMenu.h"
#include "Blueprint/WidgetTree.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/UniformGridSlot.h"
#include "Components/HorizontalBox.h"
#include "Engine.h"
#include "UI_ItemSlot_Widget.h"

void UUI_Inventory_Widget::NativeConstruct()
{

	if (Btn_Inventory_Close)
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
	}


	//SpawnSlots();
}


void UUI_Inventory_Widget::SpawnSlots()
{
	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());
	
	UUserWidget* slotWidget = controller->uiItemSlotWidget;

	for (int i = 0; i < 8; i++)
	{
		slotWidget = CreateWidget<UUserWidget>(GetWorld());
		GridPanel_ItemSlots->AddChildToGrid(slotWidget);
		MyItemSlot->AddToViewport();
	}





	//GridPanel_ItemSlots->AddChildToGrid(tempWidget);
	//UUniformGridSlot* slotBox = Cast<UUniformGridSlot>(GetWidgetFromName(FName("GridPanel_ItemSlots")));
	//UHorizontalBox* slotBox = Cast<UHorizontalBox>(GetWidgetFromName(FName("HorizontalBox_01")));
	


	//for (int i = 0; i < 5; i++)
	//{
		//uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
		//GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);

		//UUserWidget* slotWidget = WidgetTree->ConstructWidget<UUI_ItemSlot_Widget>(MyWidgetClass);

		//slotBox->AddChild(slotWidget);
	//}

	//GridPanel_ItemSlots->AddChildToGrid();


	//static ConstructorHelpers::FClassFinder<UUserWidget> myItemSlot(TEXT("/Game/_My/UI/ItemSlot_BP"));
	//if (myItemSlot.Succeeded())
	//{
	//	uiItemSlotBPClass = myItemSlot.Class;
	//}

	//if (uiItemSlotBPClass)
	//{
	//	uiItemSlotWidget = CreateWidget<UUserWidget>(GetWorld(), uiItemSlotBPClass);
	//	if (uiItemSlotWidget)
	//	{
	//		//if (GridPanel_ItemSlots)
	//		//{
	//		//	GridPanel_ItemSlots->AddChildToGrid(uiItemSlotWidget);
	//		//}
	//		uiItemSlotWidget->AddToViewport();
	//	}
	//}

	//auto GridPanel_ItemSlots = WidgetTree->ConstructWidget<UGridPanel>(UGridPanel::StaticClass());
	//if (GridPanel_ItemSlots)
	//{
	//	auto uiItemSlotBPClass = WidgetTree->ConstructWidget<UUserWidget>(UUserWidget::StaticClass());
	//	GridPanel_ItemSlots->AddChild(uiItemSlotBPClass);
	//}

}

void UUI_Inventory_Widget::Btn_Inventory_CloseWindow()
{
	//AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	//contoller->CloseInventory();
}
