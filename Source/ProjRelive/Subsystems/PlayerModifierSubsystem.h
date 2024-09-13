// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PlayerModifierSubsystem.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API UPlayerModifierSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

	UPlayerModifierSubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintImplementableEvent)
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();
};
