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
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPossessAcknowledge);

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
	AActor* ReliveCharacter;
	
	UPROPERTY(BlueprintReadWrite, Category="References")
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintReadWrite, Category="References")
	FVector ClickedLocation;
	
	UPROPERTY(BlueprintReadWrite, Category="Stats")
	float ZoomSpeed = 3.f;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnPossessAcknowledge OnPossessAcknowledge;
protected:
	virtual void AcknowledgePossession(APawn* P) override;
};
