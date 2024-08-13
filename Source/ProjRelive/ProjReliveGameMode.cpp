// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjReliveGameMode.h"
#include "ProjReliveCharacter.h"
#include "UObject/ConstructorHelpers.h"

AProjReliveGameMode::AProjReliveGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
