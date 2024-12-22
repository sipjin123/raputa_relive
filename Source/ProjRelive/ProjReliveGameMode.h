// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ProjReliveGameMode.generated.h"


class ARelivePlayerController;
class AProjReliveCharacter;
struct FDonatePlayerInfo;

UCLASS(minimalapi)
class AProjReliveGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AProjReliveGameMode(const FObjectInitializer& ObjectInitializer);

	/*
	* the key of SpawnItemInfo map is item id, and the value of SpawnItemInfo map is item
	* ErrorCode, is return code, if success is 0, others are errors
	*/
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SpawnDonationItems(const FDonatePlayerInfo& DonateInfo, const TMap<int32, int32>& SpawnItemInfo, int32& ErrorCode);


	UFUNCTION(BlueprintCallable)
	AProjReliveCharacter* FindAvatartByVTuberId(const FString& VTuberId) const;


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

	void InitWebSocket();

	void BroadcastAllDonationInfo(const FDonatePlayerInfo& DonateInfo);

	int32 DealWithDonation(const FDonatePlayerInfo& DonateInfo);

	UFUNCTION()
	void OnRequestDonate(const FDonatePlayerInfo& DonateInfo);

	UPROPERTY()
	TArray<ARelivePlayerController*> AllControllers;

};
