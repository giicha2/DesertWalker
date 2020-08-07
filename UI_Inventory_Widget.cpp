// Fill out your copyright notice in the Description page of Project Settings.


#include "UI_Inventory_Widget.h"
#include "Controller_StartMenu.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/UniformGridSlot.h"
#include "Engine.h"

void UUI_Inventory_Widget::NativeConstruct()
{

	if (Btn_Inventory_Close)
	{
		Btn_Inventory_Close->OnClicked.AddDynamic(this, &UUI_Inventory_Widget::Btn_Inventory_CloseWindow);
	}

	for (int i = 0; i < 8; i++)
	{
		SpawnSlots();
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, __FUNCTION__);
	}

}


void UUI_Inventory_Widget::SpawnSlots()
{

	AController_StartMenu* controller = Cast<AController_StartMenu>(GetOwningPlayer());
	controller->CreateItemSlots();
	UUserWidget* tempWidget = controller->uiItemSlotWidget;

	GridPanel_ItemSlots->AddChildToGrid(tempWidget);
	if (UUniformGridSlot* slot = Cast< UUniformGridSlot>(tempWidget->Slot))
	{
		slot->SetColumn(5);
		slot->SetRow(3);
	}

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
	AController_StartMenu* contoller = Cast<AController_StartMenu>(GetOwningPlayer());
	contoller->CloseInventory();
}
