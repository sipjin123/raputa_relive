// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/CooldownData.h"
#include "RelivePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API ARelivePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ARelivePlayerState();

	UFUNCTION(NetMulticast, Reliable)
	void UpdateCharacterName(const FString& ID);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UPROPERTY(BlueprintReadWrite, Replicated)
	TArray<FCooldownData> CooldownData;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int PlayerIndex;

	UFUNCTION()
	void OnRep_VTuberID(FString OldID);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_VTuberID)
	FString VTuberID;

	UPROPERTY(BlueprintReadWrite)//, Replicated)
	FString CachedCharName;

private:

};
