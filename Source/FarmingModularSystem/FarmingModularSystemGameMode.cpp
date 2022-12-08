// Copyright Epic Games, Inc. All Rights Reserved.

#include "FarmingModularSystemGameMode.h"
#include "FarmingModularSystemCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFarmingModularSystemGameMode::AFarmingModularSystemGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
