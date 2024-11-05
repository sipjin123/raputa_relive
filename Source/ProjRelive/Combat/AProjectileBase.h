
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "AProjectileBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPooledObj);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnResetObj);
UCLASS()
class PROJRELIVE_API AAProjectileBase : public AReliveActor
{
	GENERATED_BODY()
public:
	// Sets default values for this actor's properties
	AAProjectileBase();

	// Sphere collision component.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision")
	class USphereComponent* CollisionSphere;

	// Projectile movement component.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess), Category = "Movement") // Add this to ensure editor visibility in details panel
		class UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Speed = 100.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats", meta = (ExposeOnSpawn = "true"))
	float Velocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float TargetAreaRadius = 120.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stats")
	float Lifetime = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FVector SpawnLocation;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data")
	FRotator SpawnRotation;
	
	UPROPERTY(BlueprintReadWrite, Category = "Spawnable")
	AReliveActor* SpawnedTargetIndicator;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnResetObj OnResetObj;

	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnPooledObj OnPooledObj;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
};