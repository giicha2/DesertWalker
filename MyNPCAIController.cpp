// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNPCAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "blackboard_keys.h"
#include "MyPlayerCharacter.h"

AMyNPCAIController::AMyNPCAIController(FObjectInitializer const& object_initalizer)
{
	PrimaryActorTick.bCanEverTick = true;

	behavior_tree_Comp = object_initalizer.CreateAbstractDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	blackboard = object_initalizer.CreateAbstractDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));
}

void AMyNPCAIController::BeginPlay()
{
}

void AMyNPCAIController::OnPossess(APawn* Pawn)
{
}

void AMyNPCAIController::Tick(float DeltaSeconds)
{
}

FRotator AMyNPCAIController::GetControlRotation() const
{
	return FRotator();
}

void AMyNPCAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
}

UBlackboardComponent* AMyNPCAIController::get_blackboard() const
{
	return nullptr;
}

void AMyNPCAIController::setup_perception_system()
{
}
