// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjRelive/Enums/EPlayerStats.h"
#include "ProjRelive/Structs/BuffState.h"
#include "ProjRelive/Structs/DebuffState.h"

#include "PlayerModifierComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuffApplied, EBuffs, BuffType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDebuffApplied, EDebuffs, DebuffType);

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJRELIVE_API UPlayerModifierComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerModifierComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Stats")
	float CurrentBuffTimer;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Stats")
	TArray<FBuffState> AppliedBuffs;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Stats")
	TArray<FDebuffState> AppliedDebuffs;

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Application")
	void Server_ApplyBuff(EBuffs BuffToApply);
	void Server_ApplyBuff_Implementation(EBuffs BuffToApply);
	bool Server_ApplyBuff_Validate(EBuffs BuffToApply);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulticast_ExecuteBuff(EBuffs BuffToApply);
	void NetMulticast_ExecuteBuff_Implementation(EBuffs BuffToApply);

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnBuffApplied OnBuffApplied;

	UFUNCTION(BlueprintCallable)
	void ProcessBuffEffect(EBuffs BuffToApply);


	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "Application")
	void Server_ApplyDebuff(EDebuffs DebuffToApply);
	void Server_ApplyDebuff_Implementation(EDebuffs DebuffToApply);
	bool Server_ApplyDebuff_Validate(EDebuffs DebuffToApply);

	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulticast_ExecuteDebuff(EDebuffs DebuffToApply);
	void NetMulticast_ExecuteDebuff_Implementation(EDebuffs DebuffToApply);

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnDebuffApplied OnDebuffApplied;

	UFUNCTION(BlueprintCallable)
	void ProcessDebuffEffect(EDebuffs DebuffToApply);
};