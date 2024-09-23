// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "SpawnerSubsystem.generated.h"

// NOTE: This Class is Deprecated, to DELETE

DECLARE_LOG_CATEGORY_EXTERN(SpawnerISSLog, Log, All);
UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API USpawnerSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	USpawnerSubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintImplementableEvent)
	
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

	void SpawnChest(FVector Location, int ForUserId) const;
};
