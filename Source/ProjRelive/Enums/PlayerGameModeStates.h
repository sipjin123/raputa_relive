#pragma once

UENUM(BlueprintType)
enum class EGameMode : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Escort = 1 UMETA(DisplayName = "Escort"),
	Defense = 2 UMETA(DisplayName = "Defense"),
	Intelligence = 3 UMETA(DisplayName = "Intelligence"),
	Search = 4 UMETA(DisplayName = "Search"),
};

UENUM(BlueprintType)
enum class EAIType : uint8
{
	None = 0 UMETA(DisplayName = "None"),
	Dummy = 1 UMETA(DisplayName = "Dummy"),
	EscortChicken = 2 UMETA(DisplayName = "EscortChicken"),
	Wolf = 3 UMETA(DisplayName = "Wolf"),
};


struct PlayerGameModeStates
{

};