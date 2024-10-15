// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSubsystem.h"

UItemSubsystem::UItemSubsystem()
{
}

void UItemSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	InitEventCalledInBlueprint();
}

FItemData UItemSubsystem::RequestItemData(FDataTableRowHandle RowHandle)
{
	FName LocalRowName = RowHandle.RowName;
	const FItemData* OutRow = RowHandle.DataTable->FindRow<FItemData>(LocalRowName, "");
	return *OutRow;
}

FTreasureItemData UItemSubsystem::RequestTreasureItemData(FDataTableRowHandle RowHandle)
{
	FName LocalRowName = RowHandle.RowName;
	const FTreasureItemData* OutRow = RowHandle.DataTable->FindRow<FTreasureItemData>(LocalRowName, "");
	return *OutRow;
}

FDataTableRowHandle UItemSubsystem::RequestRandomDataHandle(bool isTreasureItem)
{
	TArray<FName> NewRowNames = isTreasureItem ? TreasureItemsDataTable->GetRowNames() : ItemsDataTable->GetRowNames();
	int MaxArray = NewRowNames.Num() - 1;

	if (MaxArray > 0)
	{
		//UE_LOG(LogTemp, Log, TEXT("Returning Random Name: %d"), MaxArray);
		int RandomizedValue = FMath::RandRange(0, MaxArray);

		FDataTableRowHandle NewHandle = FDataTableRowHandle();
		NewHandle.RowName = NewRowNames[RandomizedValue];
		NewHandle.DataTable = isTreasureItem ? TreasureItemsDataTable : ItemsDataTable;
		
		FString RowNameStr = NewHandle.RowName.ToString();
		//UE_LOG(LogTemp, Log, TEXT("Data table content is %s :: %d / %d"), *RowNameStr, RandomizedValue, MaxArray);
		return NewHandle;
	}
	else
	{
	UE_LOG(LogTemp, Log, TEXT("FAILED TO RETURN Random Name: %d"), MaxArray);
	}
	return DefaultItemRowHandle;
}
