// Fill out your copyright notice in the Description page of Project Settings.


#include "TreasureHuntComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UTreasureHuntComponent::UTreasureHuntComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTreasureHuntComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UTreasureHuntComponent, UserTreasureItems);
}


// Called when the game starts
void UTreasureHuntComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTreasureHuntComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

