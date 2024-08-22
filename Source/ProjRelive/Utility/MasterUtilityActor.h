// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "MasterUtilityActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API AMasterUtilityActor : public AReliveActor
{
	GENERATED_BODY()
public:
	AMasterUtilityActor();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
};
