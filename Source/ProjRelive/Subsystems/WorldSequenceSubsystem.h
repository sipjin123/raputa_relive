// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "WorldSequenceSubsystem.generated.h"

/**
 * 
 */

UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API UWorldSequenceSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

protected:
public:
	UFUNCTION(BlueprintImplementableEvent)

	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();

protected:
	virtual void Initialize(FSubsystemCollectionBase& collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
};
