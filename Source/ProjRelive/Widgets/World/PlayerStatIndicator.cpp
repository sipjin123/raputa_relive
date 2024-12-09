// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatIndicator.h"
#include "Components/TextBlock.h"

void UPlayerStatIndicator::NativeConstruct()
{
}
void UPlayerStatIndicator::UpdateCharacterName(const FString& Name)
{
	if (CharacterName)
	{
		CharacterName->SetText(FText::FromString(Name));
		CharacterName->SynchronizeProperties();
	}
}
