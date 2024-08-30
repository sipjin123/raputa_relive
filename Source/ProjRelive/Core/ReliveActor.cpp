// Fill out your copyright notice in the Description page of Project Settings.


#include "ReliveActor.h"

// Sets default values
AReliveActor::AReliveActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = SceneComponent;
	
	StaticMeshSource = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatMeshComp"));
	StaticMeshSource->SetVisibility(true);
	StaticMeshSource->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AReliveActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AReliveActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AReliveActor::HideObj()
{
}

