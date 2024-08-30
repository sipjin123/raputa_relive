// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ReliveActor.generated.h"

UCLASS()
class PROJRELIVE_API AReliveActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AReliveActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category="Visibility")
	void HideObj();
	
public:
	UPROPERTY(BlueprintReadWrite, Category="Interaction")
	bool Interactable;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Display")
	class UStaticMeshComponent* StaticMeshSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;
};
