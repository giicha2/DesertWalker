// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MyBotCharacter.h"
#include "BTTask_MeleeAttack.generated.h"

/**
 * 
 */
UCLASS()
class DESERTWALKER_API UBTTask_MeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTTask_MeleeAttack(FObjectInitializer const& object_intializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

private:
	bool montage_has_finished(AMyBotCharacter* const npcBot);
};
