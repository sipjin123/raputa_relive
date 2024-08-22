// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjRelive/ProjReliveCharacter.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "RelivePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API ARelivePlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	ARelivePlayerController();
	
	UPROPERTY(BlueprintReadWrite, Category="References")
	AProjReliveCharacter* ReliveCharacter;
	
	UPROPERTY(BlueprintReadWrite, Category="References")
	AReliveActor* CurrentTargetActor;

	UPROPERTY(BlueprintReadWrite, Category="Reference")
	FVector ClickedLocation;
};
