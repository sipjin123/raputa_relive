// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInteractable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIInteractable : public UInterface
{
	GENERATED_BODY()
};

class PROJRELIVE_API IIInteractable
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteractByActor(const AActor* ActorRef);

	UFUNCTION()
	virtual void ProcessInteractPure();
	
	UFUNCTION()
	virtual void ProcessInteractByActorPure(const AActor* ActorRef);
};