// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjReliveGameMode.generated.h"


class ARelivePlayerController;

UCLASS(minimalapi)
class AProjReliveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjReliveGameMode(const FObjectInitializer& ObjectInitializer);


protected:

	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void PostLogin(APlayerController* NewPlayerController) override;

	virtual void Logout(AController* Exiting) override;

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsThisDedicatedServer() {
		return GetWorld()->GetNetMode() == NM_DedicatedServer;
	}
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsThisListenServer() {
		return GetWorld()->GetNetMode() == NM_ListenServer;
	}
private:


	void BindCallbackFromWebsocket();

	UPROPERTY()
	TArray<ARelivePlayerController*> AllControllers;

};
