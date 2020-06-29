// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "HPBar.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API UHPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void set_bar_value_percent(float const value);
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* HPbar_value = nullptr;
	
};
