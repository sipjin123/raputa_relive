// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemData.h"
#include "GameFramework/Actor.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "ItemBase.generated.h"

UCLASS()
class PROJRELIVE_API AItemBase : public AReliveActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadWrite, Category="Data")
	FItemData ItemData;

	UPROPERTY(BlueprintReadWrite)
	bool IsPickup;
	UPROPERTY(BlueprintReadWrite)
	bool IsCopy;
	
	UPROPERTY(BlueprintReadWrite, Category="Item Data")
	UActorComponent* OwningInventory;
};
