// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "UI_Die_Widget.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API UUI_Die_Widget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GotoLobby = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_StartNewGame = nullptr;


	UFUNCTION()
		void GotoLobby();

	UFUNCTION()
		void StartNewGame();
};
