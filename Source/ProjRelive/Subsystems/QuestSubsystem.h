// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "QuestSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FQuestCompletion, int, UserId, int, QuestId);
DECLARE_LOG_CATEGORY_EXTERN(InstanceSubsystemLog, Log, All);
UCLASS(Abstract, Blueprintable)
class PROJRELIVE_API UQuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	UQuestSubsystem();

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	UFUNCTION(BlueprintImplementableEvent)
	// ReSharper disable once CppUEBlueprintImplementableEventNotImplemented
	void InitEventCalledInBlueprint();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "EventCallbacks")
	FQuestCompletion OnQuestComplete;
};
