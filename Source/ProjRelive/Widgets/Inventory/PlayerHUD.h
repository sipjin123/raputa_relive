// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySlot.h"
#include "Blueprint/UserWidget.h"
#include "Components/HorizontalBox.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UPlayerHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	UHorizontalBox* AbilityParent;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<UAbilitySlot*> AbilitySlots;
	
	UPROPERTY(BlueprintReadWrite)
	UInventoryComponent* InventoryComponentRef;
};
