// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Components/TextBlock.h"
#include "GameHUD_UI.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API UGameHUD_UI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void NativeConstruct() override;
	void set_HUDbar_value_percent(float const value);

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HUD_HPbar_value = nullptr;


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_GameMenu = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Inventory = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_Attack = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UButton* Btn_ChangeWeapon = nullptr;

private:
	UFUNCTION()
		void Btn_GameMenu_Clicked();

	UFUNCTION()
		void Btn_Inventory_Clicked();

	UFUNCTION()
		void Btn_Attack_Clicked();

	UFUNCTION()
		void Btn_ChangeWeapon_Clicked();
};
