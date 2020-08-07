// Fill out your copyright notice in the Description page of Project Settings.


#include "Player_AnimNotifyState.h"
#include "MyPlayerCharacter.h"


void UPlayer_AnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AMyPlayerCharacter* Player = Cast<AMyPlayerCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->isDuringAttack = true;
		}
	}
}

void UPlayer_AnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		AMyPlayerCharacter* Player = Cast<AMyPlayerCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->Attack_Melee_End();
			//Player->isDuringAttack = false;
		}
	}
}
