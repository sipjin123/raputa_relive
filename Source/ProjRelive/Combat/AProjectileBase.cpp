#pragma once
#include "AProjectileBase.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/StaticMesh.h"
#include "Kismet/KismetMathLibrary.h"

AAProjectileBase::AAProjectileBase()
{
    SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    RootComponent = SceneComponent;
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
    SpawnRotation = GetActorRotation();
}

// Called every frame
void AAProjectileBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}