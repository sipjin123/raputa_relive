// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "ProjRelive/Enums/EquipType.h"
#include "ItemAttachment.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FResetItem);
UCLASS()
class PROJRELIVE_API AItemAttachment : public AReliveActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemAttachment();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Item Data")
	EItemEquipSlot EquipSlotType;

	UPROPERTY(BlueprintReadWrite, BlueprintCallable, BlueprintAssignable)
	FResetItem ResetItem;
};
