// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSubsystem.h"

#include <string>


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
	//const FName LocalRowName = "Chicken";
	//const FItemData* OutRow = ItemsDataTable->FindRow<FItemData>(LocalRowName, "");
	//return *OutRow;
	try
	{
		FName LocalRowName = RowHandle.RowName;
		const FItemData* OutRow = RowHandle.DataTable->FindRow<FItemData>(LocalRowName, "");
		return *OutRow;
	}
	catch (...)
	{
		const FName LocalRowName = "Chicken";
		const FItemData* OutRow = ItemsDataTable->FindRow<FItemData>(LocalRowName, "");
		return *OutRow;
	}
}

FDataTableRowHandle UItemSubsystem::RequestRandomDataHandle()
{
	TArray<FName> NewRowNames = ItemsDataTable->GetRowNames();
	int MaxArray = NewRowNames.Num() - 1 -1; // REMOVE LANDMINE FOR NOW

	if (MaxArray > 0)
	{
		int RandomizedValue = FMath::RandRange(0, MaxArray);

		FDataTableRowHandle NewHandle = FDataTableRowHandle();
		NewHandle.RowName = NewRowNames[RandomizedValue];
		NewHandle.DataTable = ItemsDataTable;
		
		FString RowNameStr = NewHandle.RowName.ToString();
		UE_LOG(LogTemp, Log, TEXT("Data table content is %s :: %d / %d"), *RowNameStr, RandomizedValue, MaxArray);
		return NewHandle;
	}
	return DefaultItemRowHandle;
}
