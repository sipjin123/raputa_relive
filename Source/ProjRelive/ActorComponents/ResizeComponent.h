// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <ProjRelive/Enums/EPlayerStats.h>
#include "ResizeComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnShrink);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetVariables);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEnlarge);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFinishResize);
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJRELIVE_API UResizeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UResizeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnShrink OnShrink;

	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnEnlarge OnEnlarge;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnFinishResize OnFinishResize;
	UPROPERTY(BlueprintCallable, BlueprintAssignable, Category = "Delegates")
	FOnResetVariables OnResetVariables;

	UFUNCTION(BlueprintCallable)
	void Enlarge(bool ShouldDestroyOnEnd);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_Enlarge(bool ShouldDestroyOnEnd);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulti_Enlarge(bool ShouldDestroyOnEnd);

	UFUNCTION(BlueprintCallable)
	void Shrink(bool ShouldDestroyOnEnd);
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_Shrink(bool ShouldDestroyOnEnd);
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulti_Shrink(bool ShouldDestroyOnEnd);

	UFUNCTION(BlueprintCallable)
	void OverrideShrinkSpeed(float NewSpeed);
	UFUNCTION(BlueprintCallable)
	void OverrideEnlargeSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable)
	void FinishResizing();
	UFUNCTION(BlueprintCallable)
	void ResetScale();
	UFUNCTION(BlueprintCallable)
	void ResetVariables();
	UFUNCTION(BlueprintCallable)
	void RegisterOriginScale();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State")
	bool IsShrinking();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State")
	bool IsEnlarging();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "State")
	bool CanResize();

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "State")
	bool IsResizing;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "State")
	bool DestroyOnEnd;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "State")
	bool HideOnEnd;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "State")
	bool UseMeshOnly;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "State")
	FVector OriginScale;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	EResizeState ResizeState = EResizeState::None;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Stats")
	EActorType ActorType;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float ShrinkSpeed = 2.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float EnlargeSpeed = 3.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float StrinkLerpVal = 0.0f;
	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	float EnlargeLerpVal = 0.0f;
};
