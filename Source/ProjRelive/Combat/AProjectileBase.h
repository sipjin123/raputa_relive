
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "AProjectileBase.generated.h"

UCLASS()
class PROJRELIVE_API AAProjectileBase : public AReliveActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	//AAProjectileBase();

	// Sphere collision component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* CollisionSphere;

	// Projectile movement component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess), Category = "Movement") // Add this to ensure editor visibility in details panel
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	class UStaticMeshComponent* StaticMeshSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (ExposeOnSpawn = "true"))
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float TargetAreaRadius = 120.f;

	UPROPERTY(BlueprintReadWrite, Category = "Spawnable")
	AReliveActor* SpawnedTargetIndicator;
};