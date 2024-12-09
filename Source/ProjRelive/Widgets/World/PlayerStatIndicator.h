// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatIndicator.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJRELIVE_API UPlayerStatIndicator : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateCharacterName(const FString& Name);

	UPROPERTY(BlueprintReadWrite, Category = ">Tips", Meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterName;

protected:
	virtual void NativeConstruct() override;

};
