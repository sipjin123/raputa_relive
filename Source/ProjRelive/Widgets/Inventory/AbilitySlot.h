// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ProjRelive/ActorComponents/InventoryComponent.h"
#include "ProjRelive/Items/ItemData.h"
#include "AbilitySlot.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UAbilitySlot : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	UPROPERTY(BlueprintReadWrite)
	int SlotId = -1;
	
	UPROPERTY(BlueprintReadWrite)
	FItemData ItemData;
	
	UPROPERTY(BlueprintReadWrite)
	UInventoryComponent* InventoryComponentRef;
	
	UPROPERTY(BlueprintReadWrite)
	UPlayerHUD* PlayerHUD;
};
