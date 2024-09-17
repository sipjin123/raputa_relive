// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjRelive/Items/ItemData.h"
#include "InventoryPanel.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UInventoryPanel : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

public:
};
