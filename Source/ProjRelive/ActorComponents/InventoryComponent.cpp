// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ProjRelive/Widgets/Inventory/InventoryPanel.h"
#include "ProjRelive/Widgets/Inventory/PlayerHUD.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	// ...
	if(IsValid(InventoryWidget))
	{
		InventoryPanel = CreateWidget<UInventoryPanel>(GetWorld(), InventoryWidget);
	}
	if(IsValid(PlayerHUDWidget))
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidget);
		//PlayerHUD->AddToViewport();
	}

	Super::BeginPlay();

	/* Assign Empty Entries, Moved to Blueprint for Actor Assignments
	for (EPowerupType myPowerupType = EPowerupType::begin; myPowerupType < EPowerupType::end;
		myPowerupType = static_cast<EPowerupType>((size_t)myPowerupType + 1))
	{
		FString EnumAsString = UEnum::GetDisplayValueAsText(myPowerupType).ToString();
		EquipmentDisplay.Add(myPowerupType, nullptr);
	}*/
}

void UInventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UInventoryComponent, CurrentEquippedItem);
	DOREPLIFETIME(UInventoryComponent, CurrentAbilityId);
	DOREPLIFETIME(UInventoryComponent, CurrentSlotSelected);
	DOREPLIFETIME(UInventoryComponent, EquippedUserAbilities);
	DOREPLIFETIME(UInventoryComponent, UserItems);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::CloseInventory()
{
	if (IsValid(InventoryPanel) && IsInventoryOpen)
	{
		IsInventoryOpen = false;
		InventoryPanel->RemoveFromParent();
	}
}

void UInventoryComponent::OpenInventory()
{
	if (IsValid(InventoryPanel) && !IsInventoryOpen)
	{
		IsInventoryOpen = true;
		InventoryPanel->AddToViewport(0);
	}
}

void UInventoryComponent::AddItemToInventory(FItemData ItemData, int QuantityOverride)
{
	//UE_LOG(LogTemp, Log, TEXT("Adding Item To Inventory C++: {%d}"), ItemData.Id);

	// Find existing Inventory if Any
	auto ExistingItemIndex = UserItems.IndexOfByPredicate([ItemData](const FItemData& InItem)
		{
			return InItem.Id == ItemData.Id;
		});
	bool DisableAddInventory = false;

	if (!DisableAddInventory) {
		if (ExistingItemIndex >= 0 && UserItems.Num() > ExistingItemIndex)
		{
			// Increment the quantity of Inventory Slots
			if (QuantityOverride > 0)
			{
				UserItems[ExistingItemIndex].Quantity += QuantityOverride;
			}
			else
			{
				UserItems[ExistingItemIndex].Quantity += ItemData.Quantity;
			}

			// Increment the quantity of Ability Slots
			for (int i = 0; i < EquippedUserAbilities.Num(); i++)
			{
				if (ItemData.Id == EquippedUserAbilities[i].ItemId)
				{
					EquippedUserAbilities[i].ItemData.Quantity = UserItems[ExistingItemIndex].Quantity;
				}
			}
		}
		else
		{
			if (QuantityOverride > 0)
			{
				ItemData.Quantity = QuantityOverride;
			}

			// Add new Item to Inventory
			UserItems.Add(ItemData);

			for (int i = 0; i < EquippedUserAbilities.Num(); i++) {
				// Find a slot with no Item Assignment and inject item there
				if (EquippedUserAbilities[i].ItemId < 0) {
					EquippedUserAbilities[i].ItemId = ItemData.Id;
					EquippedUserAbilities[i].PowerupType = ItemData.PowerupType;
					EquippedUserAbilities[i].ItemData = ItemData;
					break;
				}
			}
		}
	}
	OnInventoryModified.Broadcast();
}

void UInventoryComponent::SyncUserItems()
{
}

void UInventoryComponent::OnRep_SetEquippedUserAbilities()
{
	OnInventoryModifiedByServer.Broadcast();
}

void UInventoryComponent::ConsumeItem(int ItemId, int ConsumeAmount)
{
	// Find existing Inventory if Any
	auto ExistingItemIndex = UserItems.IndexOfByPredicate([ItemId](const FItemData& InItem)
		{
			return InItem.Id == ItemId;
		});

	if (ExistingItemIndex >= 0 && UserItems.Num() > ExistingItemIndex)
	{
		//UE_LOG(LogTemp, Log, TEXT("Consuming item: {%d}"), ItemId);
		UserItems[ExistingItemIndex].Quantity --;
		if (UserItems[ExistingItemIndex].Quantity <= 0)
		{
			UE_LOG(LogTemp, Log, TEXT("Depleted a Consumable Item From Inventory C++: {%d}"), ItemId);
			// Remove Inventory Item if fully consumed
			UserItems.RemoveAt(ExistingItemIndex);

			// Remove Equipped Item if fully consumed
			FEquippedAbilities* FoundEntry = EquippedUserAbilities.FindByPredicate([ItemId](const FEquippedAbilities& InItem)
			{
				return InItem.ItemId == ItemId;
			});
			
			auto FoundIndex = EquippedUserAbilities.IndexOfByPredicate([ItemId](const FEquippedAbilities& InItem)
			{
				return InItem.ItemId == ItemId;
			});

			if (FoundIndex >= 0)
			{
				//UE_LOG(LogTemp, Log, TEXT("Removing Item: {%d} -- {%s} -- {%d}"), FoundEntry->Id, *FoundEntry->ItemTextData.Name.ToString(), FoundIndex);
				EquippedUserAbilities[FoundIndex].ClearContent();
			}
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Consumed a Stack of Item From Inventory C++: {%d} Remain:{%d}"), ItemId, UserItems[ExistingItemIndex].Quantity);
		}
		SyncAbilityPanelItems();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to Consume--> ItemId: {%d} ExistingItem:{%d} UserItemCount:{%d}"), ItemId, ExistingItemIndex, UserItems.Num());
		for (int i = 0; i < UserItems.Num(); i++) {

			FString EnumAsString = UEnum::GetDisplayValueAsText(UserItems[i].PowerupType).ToString();
			UE_LOG(LogTemp, Log, TEXT("Failed to Consume--> ItemId: {%d}-{%s} "), UserItems[i].Id, *EnumAsString);
		}

	}
	OnInventoryModified.Broadcast();
}

void UInventoryComponent::SyncAbilityPanelItems()
{
	TArray<int> ItemsToRemove;
	for (int i = 0; i < EquippedUserAbilities.Num(); i++)
	{
		int EquippedItemId = EquippedUserAbilities[i].ItemId;
		auto UserItemIndex = UserItems.IndexOfByPredicate([EquippedItemId](const FItemData& InItem)
			{
				return InItem.Id == EquippedItemId;
			});
		if(UserItemIndex >= 0)
		{
			EquippedUserAbilities[i].ItemData.Quantity = UserItems[UserItemIndex].Quantity;
		}
		else
		{
			ItemsToRemove.Add(i);
		}
	}
	if (ItemsToRemove.Num() > 0)
	{
		for (int i = 0; i < ItemsToRemove.Num(); i++)
		{
			int itemIdToClear = ItemsToRemove[i];
			EquippedUserAbilities[itemIdToClear].ClearContent();
		}
	}
}

void UInventoryComponent::ClearCurrentEquippedAbility()
{
	if (CurrentSlotSelected >= 0) {
		FString EnumAsString = UEnum::GetDisplayValueAsText(EquippedUserAbilities[CurrentSlotSelected].PowerupType).ToString();
		UE_LOG(LogTemp, Log, TEXT("Slot: {%d} -- Clearing Ability: {%d}::{%s}"), CurrentSlotSelected, EquippedUserAbilities[CurrentSlotSelected].ItemId, *EnumAsString);
		EquippedUserAbilities[CurrentSlotSelected].ClearContent();
	}
}

FItemData UInventoryComponent::GetUserItemById(int ItemId)
{
	FItemData* FoundEntry = UserItems.FindByPredicate([ItemId](const FItemData& InItem)
		{
			return InItem.Id == ItemId;
		});

	auto UserItemIndex = UserItems.IndexOfByPredicate([ItemId](const FItemData& InItem)
		{
			return InItem.Id == ItemId;
		});
	if (UserItemIndex >= 0) {
		FItemData NewItemData = UserItems[UserItemIndex];
		return NewItemData;
	}
	return FItemData();
}

FItemData UInventoryComponent::GetUserItemByType(EPowerupType ItemType)
{
	auto UserItemIndex = UserItems.IndexOfByPredicate([ItemType](const FItemData& InItem)
		{
			return InItem.PowerupType == ItemType;
		});

	if (UserItemIndex >= 0) {
		FItemData NewItemData = UserItems[UserItemIndex];
		return NewItemData;
	}
	return FItemData();
}

