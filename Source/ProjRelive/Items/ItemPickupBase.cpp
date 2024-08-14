// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPickupBase.h"

// Sets default values
AItemPickupBase::AItemPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

