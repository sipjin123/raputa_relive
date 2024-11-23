// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjReliveGameMode.generated.h"

UCLASS(minimalapi)
class AProjReliveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjReliveGameMode();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsThisDedicatedServer() {
		return GetWorld()->GetNetMode() == NM_DedicatedServer;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsThisListenServer() {
		return GetWorld()->GetNetMode() == NM_ListenServer;
	}
};



