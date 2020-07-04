// Fill out your copyright notice in the Description page of Project Settings.


#include "StartMenu_GameMode.h"
#include "StartMenu_HUD.h"
#include "StartMenu_Controller.h"

AStartMenu_GameMode::AStartMenu_GameMode()
{
	HUDClass = AStartMenu_HUD::StaticClass();
	DefaultPawnClass = nullptr;
	PlayerControllerClass = AStartMenu_Controller::StaticClass();
}
