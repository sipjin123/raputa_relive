// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include <ProjRelive/Enums/PlayerGameModeStates.h>
#include <ProjRelive/Structs/GameModeSchedule.h>
#include "WorldSequenceSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeEnd, EGameMode, EndedGameMode);
UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API UWorldSequenceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
public:
	UFUNCTION(BlueprintImplementableEvent)

	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

	UPROPERTY(BlueprintReadWrite)
	TArray<EGameMode> GameModeArraySequence;

	UPROPERTY(BlueprintReadWrite)
	TArray<FGameModeSchedule> GameModeSchedules;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnGameModeEnd OnGameModeEnd;

	UPROPERTY(BlueprintReadWrite)
	int CurrentSlotFrame = 0;

	UPROPERTY(BlueprintReadWrite)
	float CurrentTimerTick = 0;

	UPROPERTY(BlueprintReadWrite)
	FDateTime StartTime;

protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
