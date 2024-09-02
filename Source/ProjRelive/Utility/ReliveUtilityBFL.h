// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ProjRelive/Subsystems/ReliveGameInstance.h"
#include "ReliveUtilityBFL.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API UReliveUtilityBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	
	static UReliveGameInstance* CachedReliveGI;
	
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "ManagerReference", meta = (WorldContext = WorldContextObject))
	static UReliveGameInstance* ReliveGameInstance(UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper", meta = (WorldContext = WorldContextObject))
	static TArray<FGameplayTag> TagsInContainer(FGameplayTagContainer  container);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Helper", meta = (WorldContext = WorldContextObject))
	static bool IsEditorMode()
	{
#if WITH_EDITOR
		return true;
#else
		return false;
#endif
	}
};
