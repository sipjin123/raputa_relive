// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ReliveGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UReliveGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite)
	int PlayerCount;
	
	UFUNCTION(BlueprintCallable)
	void TestFunc();
};
