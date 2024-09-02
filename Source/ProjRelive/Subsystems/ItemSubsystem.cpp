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
	//const FName LocalRowName = "Chicken";
	//const FItemData* OutRow = ItemsDataTable->FindRow<FItemData>(LocalRowName, "");
	//return *OutRow;
	
	FName LocalRowName = RowHandle.RowName;
	const FItemData* OutRow = RowHandle.DataTable->FindRow<FItemData>(LocalRowName, "");
	return *OutRow;
	/*
	try
	{
	}
	catch (...)
	{
		const FName LocalRowName = "Chicken";
		const FItemData* OutRow = ItemsDataTable->FindRow<FItemData>(LocalRowName, "");
		return *OutRow;
	}*/
}

FDataTableRowHandle UItemSubsystem::RequestRandomDataHandle()
{
	TArray<FName> NewRowNames = ItemsDataTable->GetRowNames();
	int MaxArray = NewRowNames.Num() - 1;

	if (MaxArray > 0)
	{
		//UE_LOG(LogTemp, Log, TEXT("Returning Random Name: %d"), MaxArray);
		int RandomizedValue = FMath::RandRange(0, MaxArray);

		FDataTableRowHandle NewHandle = FDataTableRowHandle();
		NewHandle.RowName = NewRowNames[RandomizedValue];
		NewHandle.DataTable = ItemsDataTable;
		
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
