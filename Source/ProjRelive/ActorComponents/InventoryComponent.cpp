// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryComponent.h"

#include "ProjRelive/Widgets/Inventory/InventoryPanel.h"
#include "ProjRelive/Widgets/Inventory/PlayerHUD.h"

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
	Super::BeginPlay();

	// ...
	if(IsValid(InventoryWidget))
	{
		InventoryPanel = CreateWidget<UInventoryPanel>(GetWorld(), InventoryWidget);
	}
	if(IsValid(PlayerHUDWidget))
	{
		PlayerHUD = CreateWidget<UPlayerHUD>(GetWorld(), PlayerHUDWidget);
		PlayerHUD->AddToViewport();
	}
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
		InventoryPanel->UserItems = UserItems;
		InventoryPanel->AddToViewport(0);
	}
}

void UInventoryComponent::AddItemToInventory(FItemData ItemData)
{
	if (UserItems.Contains(ItemData.Id))
	{
		// Increment the quantity of Inventory Slots
		UserItems[ItemData.Id].Quantity += ItemData.Quantity;

		// Increment the quantity of Ability Slots
		for(int i = 0 ; i < UserEquippedAbilities.Num() ; i ++)
		{
			if(ItemData.Id == UserEquippedAbilities[i].Id)
			{
				UserEquippedAbilities[i].Quantity = UserItems[ItemData.Id].Quantity;
			}
		}
	}
	else
	{
		UserItems.Add(ItemData.Id, ItemData);
		UserEquippedAbilities.Add(ItemData);
	}

	if (UserEquippedAbilities.Num() <= 0)
	{
		UserEquippedAbilities.Add(ItemData);
	}

	PlayerHUD->UserEquippedAbilities = UserEquippedAbilities;
	OnInventoryModified.Broadcast();
}

void UInventoryComponent::SyncUserItems()
{
	InventoryPanel->UserItems = UserItems;
}

void UInventoryComponent::ConsumeItem(int ItemId, int ConsumeAmount)
{
	if (UserItems.Contains(ItemId))
	{
		//UE_LOG(LogTemp, Log, TEXT("Consuming item: {%d}"), ItemId);
		UserItems[ItemId].Quantity --;
		if (UserItems[ItemId].Quantity <= 0)
		{
			// Remove Inventory Item if fully consumed
			UserItems.Remove(ItemId);

			// Remove Equipped Item if fully consumed
			FItemData* FoundEntry = UserEquippedAbilities.FindByPredicate([ItemId](const FItemData& InItem)
			{
				return InItem.Id == ItemId;
			});
			
			auto FoundIndex = UserEquippedAbilities.IndexOfByPredicate([ItemId](const FItemData& InItem)
			{
				return InItem.Id == ItemId;
			});

			if (FoundIndex >= 0)
			{
				//UE_LOG(LogTemp, Log, TEXT("Removing Item: {%d} -- {%s} -- {%d}"), FoundEntry->Id, *FoundEntry->ItemTextData.Name.ToString(), FoundIndex);
				UserEquippedAbilities.RemoveAt(FoundIndex);
			}
			PlayerHUD->UserEquippedAbilities = UserEquippedAbilities;
		}
		SyncAbilityPanelItems();
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Failed to Consume item: {%d}"), ItemId);
	}
	OnInventoryModified.Broadcast();
}

void UInventoryComponent::SyncAbilityPanelItems()
{
	TArray<int> ItemsToRemove;
	for (int i = 0; i < UserEquippedAbilities.Num(); i++)
	{
		int EquippedItemId = UserEquippedAbilities[i].Id;
		if(UserItems.Contains(EquippedItemId))
		{
			UserEquippedAbilities[i].Quantity = UserItems[EquippedItemId].Quantity;
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
			UserEquippedAbilities.RemoveAt(ItemsToRemove[i]);
		}
	}
	PlayerHUD->UserEquippedAbilities = UserEquippedAbilities;
}

