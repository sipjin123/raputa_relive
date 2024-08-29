// Fill out your copyright notice in the Description page of Project Settings.


#include "MountBase.h"

#include "ProjRelive/Utility/ConstantsUtility.h"

// Sets default values
AMountBase::AMountBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMountBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMountBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMountBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

