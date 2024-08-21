// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "ProjRelive/Interface/IInteractable.h"
#include "TriggeredDoor.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorOpened);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDoorClosed);
UCLASS()
class PROJRELIVE_API ATriggeredDoor : public AReliveActor, public IIInteractable
{
	GENERATED_BODY()

public:
	virtual void OnInteract_Implementation() override;
	virtual void OnInteractByActor_Implementation(const AReliveActor* RActorRef) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OpenDoor();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void CloseDoor();

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnDoorOpened OnDoorOpened;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnDoorOpened OnDoorClosed;
};
