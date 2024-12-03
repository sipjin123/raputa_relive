// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Structs/CooldownData.h"
#include "RelivePlayerState.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API ARelivePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	ARelivePlayerState();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:

	UFUNCTION()
	void SetSelfCharacter(AProjReliveCharacter* Character);

	UPROPERTY(BlueprintReadWrite, Replicated)
	TArray<FCooldownData> CooldownData;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int PlayerIndex;

	UFUNCTION()
	void OnRep_CharacterName(FString OldName);
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CharacterName)
	FString CharacterName;


private:

	UPROPERTY()
	TWeakObjectPtr<AProjReliveCharacter> SelfCharacter = nullptr;

};
