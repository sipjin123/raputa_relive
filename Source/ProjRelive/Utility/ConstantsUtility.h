// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include <ProjRelive/Enums/EquipType.h>
#include <ProjRelive/Enums/PlayerCombatState.h>

#include "ConstantsUtility.generated.h"

namespace ConstantsTest
{
	static const FString Comma(TEXT(","));
	static const FString Equals(TEXT("="));
	static const FString DoubleQuote(TEXT("\""));
	static const FString SingleQuote(TEXT("'"));
	static const FString Slash(TEXT("/"));
	static const FString Backslash(TEXT("\\"));
	static const FString Custom(TEXT("custom"));
	static const FString CustomInt(TEXT("customint"));
	static const FString CustomFloat(TEXT("customfloat"));
}

/**
 * 
 */
//extern const FString HeadSocket = "HeadSocket";
UCLASS()
class PROJRELIVE_API UConstantsUtility : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	FName LeftArmSocket = "";
	FName RightArmSocket = "";

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper2", meta = (WorldContext = WorldContextObject))
	static FName GetSocketName(EItemEquipSlot ItemSlot)
	{
		switch (ItemSlot)
		{
		case EItemEquipSlot::None:
			break;
		case EItemEquipSlot::RightHand:
			return "RightArmSocket";
		case EItemEquipSlot::LeftHand:
			return "LeftArmSocket";
		case EItemEquipSlot::Back:
			return "BackpackSocket";
		case EItemEquipSlot::Front:
			return "FrontSocket";
		case EItemEquipSlot::Head:
			return "HeadSocket";
		case EItemEquipSlot::Mount:
			return "Mount";
		case EItemEquipSlot::Orbit:
			return "Orbit";
		default:
			break;
		}

		return "";
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper2", meta = (WorldContext = WorldContextObject))
	static EItemEquipSlot GetEquipSlotForPowerup(EPowerupType PowerupType) {
		switch (PowerupType)
		{
		case EPowerupType::None:
			return EItemEquipSlot::None;
		case EPowerupType::Chicken:
			return EItemEquipSlot::Back;
		case EPowerupType::Speed:
			return EItemEquipSlot::Back;
		case EPowerupType::Shield:
			return EItemEquipSlot::Back;
		case EPowerupType::BaseballBat:
			return EItemEquipSlot::RightHand;
		case EPowerupType::Landmine:
			return EItemEquipSlot::RightHand;
		default:
			return EItemEquipSlot::None;
		}
	}

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper2", meta = (WorldContext = WorldContextObject))
	static FString GetTableRow(EPowerupType PowerupType) {
		switch (PowerupType)
		{
		case EPowerupType::Chicken:
			return "Chicken";
		case EPowerupType::Speed:
			return "Speedup";
		case EPowerupType::Shield:
			return "Shield";
		case EPowerupType::BaseballBat:
			return "BaseballBat";
		case EPowerupType::Landmine:
			return "Landmine";
		case EPowerupType::Bighead:
			return "Bighead";
		case EPowerupType::Teleporter:
			return "Teleporter";
		case EPowerupType::Invinsibility:
			return "Invinsibility";
		case EPowerupType::Invisibility:
			return "Invisibility";
		case EPowerupType::None:
		default:			
			return "None";
		}
	}
};

namespace DebuffConst
{
	static const FString STUN = "Stun";
}