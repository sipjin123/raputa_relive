#pragma once
#include "AProjectileBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"


/*
// Sets default values
AAProjectileBase::AAProjectileBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    //SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    //RootComponent = SceneComponent;

    CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
    CollisionSphere->SetSphereRadius(15);
    CollisionSphere->SetCollisionProfileName("SphereCollision");

    RootComponent = CollisionSphere;
    //CollisionSphere->SetupAttachment(RootComponent);

    StaticMeshSource = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StatMeshComp"));
    StaticMeshSource->SetVisibility(true);
    StaticMeshSource->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

    if (!ProjectileMovementComponent)
    {
        // Use this component to drive this projectile's movement.
        ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
        ProjectileMovementComponent->SetUpdatedComponent(RootComponent);
        ProjectileMovementComponent->InitialSpeed = 1500.0f;
        ProjectileMovementComponent->MaxSpeed = 1500.0f;
        ProjectileMovementComponent->bRotationFollowsVelocity = true;
        ProjectileMovementComponent->bShouldBounce = true;
        ProjectileMovementComponent->Bounciness = 0.3f;
        ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
    }
}

// Called when the game starts or when spawned
void AAProjectileBase::BeginPlay()
{
    Super::BeginPlay();
    SpawnLocation = GetActorLocation();
}

// Called every frame
void AAProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}
#include "AProjectileBase.h"
// Fill out your copyright notice in the Description page of Project Settings.
*/
