// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyBasicCharacter.h"
#include "Engine/DataTable.h"
#include "MyPlayerCharacter.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FCharacterInfo :public FTableRowBase
{
	GENERATED_BODY()
public:
	FCharacterInfo()
	{
		CharacterName = FText::FromString("Name");
		CharacterLevel = 1;
		Description = FText::FromString("My Character is ....");
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName CharacterID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText CharacterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UTexture2D* CharacterThumbnail;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 CharacterLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 PlayerGold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Description;
};



UCLASS()
class DESERTWALKER_API AMyPlayerCharacter : public AMyBasicCharacter
{
	GENERATED_BODY()

public:
		AMyPlayerCharacter();

		// Called when the game starts or when spawned
		virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
		class UCameraComponent* FollowCamera;

	virtual void PostInitializeComponents()override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)override;
	void MoveForward(float value);
	void MoveRight(float value);

public:
	void Attack_Melee();
	void Attack_Melee_End();
	int getNextLevel();
	void setNextLevel(int value);
	void tempLevelNum(int value);

	//PlayerItem Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> MyItemArray_ch;

	//ShopItem Array
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<int32> ShopItemArray_ch;

	//Map Gateway
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int UserMapLevel;

		int tmpMapLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> arrMapName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		FString MapName;
};
