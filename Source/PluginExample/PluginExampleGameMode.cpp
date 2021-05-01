// Copyright Epic Games, Inc. All Rights Reserved.

#include "PluginExampleGameMode.h"
#include "PluginExamplePlayerController.h"
#include "PluginExampleCharacter.h"
#include "UObject/ConstructorHelpers.h"

APluginExampleGameMode::APluginExampleGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = APluginExamplePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}