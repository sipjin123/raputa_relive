// Fill out your copyright notice in the Description page of Project Settings.


#include "CheatComponent.h"

#include "ProjRelive/Widgets/Utility/DevCheatWidget.h"

// Sets default values for this component's properties
UCheatComponent::UCheatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCheatComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	if(IsValid(DevCheatWidgetClass))
	{
		DevCheatWidget = CreateWidget<UDevCheatWidget>(GetWorld(), DevCheatWidgetClass);
	}

	if (IsValid(HostWidgetClass))
	{
		//HostWidget = CreateWidget<UHostControlsWidget>(GetWorld(), HostWidgetClass);
	}
}


// Called every frame
void UCheatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

