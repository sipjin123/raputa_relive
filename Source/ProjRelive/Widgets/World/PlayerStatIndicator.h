// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatIndicator.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UPlayerStatIndicator : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
};
