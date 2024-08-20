// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "UObject/Interface.h"
#include "IProjectile.generated.h"

/**
 * 
 */
UINTERFACE(MinimalAPI)
class UIProjectile : public UInterface
{
	GENERATED_BODY()
};

class PROJRELIVE_API IIProjectile {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	AReliveActor* GetTargetActor();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	void SetTargetActor(AReliveActor* NewTargetActor);
};