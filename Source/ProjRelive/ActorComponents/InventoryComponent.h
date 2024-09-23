// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ProjRelive/Items/ItemData.h"
#include <ProjRelive/Structs/EquippedAbilities.h>
#include "InventoryComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryModifiedByServer);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryModified);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryOpen);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryClose);
UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJRELIVE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable)
	void CloseInventory();
	UFUNCTION(BlueprintCallable)
	void OpenInventory();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> InventoryWidget;

	UPROPERTY(BlueprintReadWrite)
	class UInventoryPanel* InventoryPanel;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UUserWidget> PlayerHUDWidget;

	UPROPERTY(BlueprintReadWrite)
	class UPlayerHUD* PlayerHUD;

	UPROPERTY(BlueprintReadWrite)
	ACharacter* CharacterRef;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnInventoryOpen OnInventoryOpen;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnInventoryClose OnInventoryClose;
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnInventoryModified OnInventoryModified;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnInventoryModifiedByServer OnInventoryModifiedByServer;

	UPROPERTY(BlueprintReadWrite)
	bool IsInventoryOpen;
	
	UFUNCTION(BlueprintCallable)
	void AddItemToInventory(FItemData ItemData);
	UFUNCTION(BlueprintCallable)
	void SyncUserItems();

	UPROPERTY(BlueprintReadWrite)
	TMap<EPowerupType, AActor*> EquipmentDisplay;

	UPROPERTY(BlueprintReadWrite, Replicated)
	TArray<FItemData> UserItems;

	//UPROPERTY(BlueprintReadWrite, Replicated)
	UPROPERTY(BlueprintReadWrite, ReplicatedUsing = OnRep_SetEquippedUserAbilities)
	TArray<FEquippedAbilities> EquippedUserAbilities;

	UFUNCTION()
	virtual void OnRep_SetEquippedUserAbilities();

	UFUNCTION(BlueprintCallable, meta=(DisplayName="ConsumeItemById"))
	void ConsumeItem(int ItemId, int ConsumeAmount);

	UFUNCTION(Blueprintable)
	void SyncAbilityPanelItems();

	UPROPERTY(BlueprintReadWrite, Replicated)
	AItemAttachment* CurrentEquippedItem;

	UPROPERTY(BlueprintReadWrite, Replicated)
	int CurrentAbilityId;
	UPROPERTY(BlueprintReadWrite, Replicated)
	int CurrentSlotSelected;

	UFUNCTION(BlueprintCallable)
	void ClearCurrentEquippedAbility();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData GetUserItemById(int ItemId);
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FItemData GetUserItemByType(EPowerupType ItemType);
};
