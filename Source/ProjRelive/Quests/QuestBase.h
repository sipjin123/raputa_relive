// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "QuestBaseData.h"
#include "QuestBase.generated.h"

UCLASS()
class UQuestBase : public UObject
{
	GENERATED_BODY()
public:
	UQuestBase();
public:
	UPROPERTY(VisibleAnywhere, Category="Item Data")
	int32 QuestId;
	UPROPERTY(VisibleAnywhere, Category="Item Data", meta=(UIMin=1, UIMax=100))
	int32 Quantity;

	UPROPERTY(VisibleAnywhere, Category="Item Data")
	UQuestBaseData* QuestDataRef;
};