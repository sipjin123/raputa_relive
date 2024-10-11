// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IDamageable.generated.h"

UINTERFACE(MinimalAPI)
class UIDamageable : public UInterface
{
	GENERATED_BODY()
};

class PROJRELIVE_API IIDamageable {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	AReliveActor* GetTargetActor();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	void SetTargetActor(AReliveActor* NewTargetActor);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnTakeDamage(float damage);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnTakeDamageByActor(AActor* actor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Combat")
	void OnPlayDeathAnim();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category="Combat")
	bool IsStunned();
};