// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include <ProjRelive/Enums/PlayerGameModeStates.h>
#include "ReliveGameState.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameModeChange, EGameMode, NewGameMode);
UCLASS()
class PROJRELIVE_API AReliveGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	AReliveGameState();
	virtual ~AReliveGameState() = default;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 TestInt = 0;

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool IsSinglePlayer = false;

	UFUNCTION(BlueprintCallable, Category = "GameMode")
	void ChangeGameMode(EGameMode NewGameMode);

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "GameMode")
	EGameMode CurrentGameMode;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "GameMode")
	EGameMode PreviousGameMode;
	UPROPERTY(BlueprintReadWrite, Category = "GameMode")
	FGameModeChange GameModeChanged;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "GameMode")
	bool IsTreasureHuntActive;
};
