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
	if (IsValid(InventoryPanel))
	{
		InventoryPanel->RemoveFromParent();
	}
}

void UInventoryComponent::OpenInventory()
{
	if (IsValid(InventoryPanel))
	{
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

