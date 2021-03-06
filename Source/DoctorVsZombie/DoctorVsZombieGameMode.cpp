// Copyright Epic Games, Inc. All Rights Reserved.

#include "DoctorVsZombieGameMode.h"
#include "DoctorVsZombiePlayerController.h"
#include "DoctorVsZombieCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADoctorVsZombieGameMode::ADoctorVsZombieGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ADoctorVsZombiePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}