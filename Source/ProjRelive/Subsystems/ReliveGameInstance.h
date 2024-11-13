// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include <ProjRelive/ProjReliveCharacter.h>
#include "ReliveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UReliveGameInstance : public UGameInstance
{
	GENERATED_BODY()

protected:
	//virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UPROPERTY(BlueprintReadWrite)
	int PlayerCount;
	
	UFUNCTION(BlueprintCallable)
	void TestFunc();

	UFUNCTION(BlueprintCallable)
	FString GetLobbyScene() const { return "LobbyScene"; }
	UFUNCTION(BlueprintCallable)
	FString GetMainScene() const { return "ReliveMain"; }
	UFUNCTION(BlueprintCallable)
	float GetWorldZGround() const { return 130.0f; }
	UFUNCTION(BlueprintCallable)
	float GetChestsZGround() const { return 10.0f; }

	UPROPERTY(BlueprintReadWrite)
	AProjReliveCharacter* HostCharacter;

	UPROPERTY(BlueprintReadWrite)
	int HostPlayerId;

	//FString GetMainScene() const { return "ReliveMain"; }
};
