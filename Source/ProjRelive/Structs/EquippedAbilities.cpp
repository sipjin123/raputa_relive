// Fill out your copyright notice in the Description page of Project Settings.


#include "EquippedAbilities.h"

void FEquippedAbilities::ClearContent()
{
	ItemId = -1;
	PowerupType = EPowerupType::None;
	ItemData = FItemData();
}
