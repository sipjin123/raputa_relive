// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ResizeComponent.h"
#include "MorphComponent.generated.h"


UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROJRELIVE_API UMorphComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMorphComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void ApplyMorphEffect();
	UFUNCTION(BlueprintCallable)
	void ReleaseMorphEffect();

	UPROPERTY(BlueprintReadWrite, Replicated)
	bool IsMorphed;

	UPROPERTY(BlueprintReadWrite, Category = "Reference")
	AActor* SpawnedActorRef;

	UPROPERTY(BlueprintReadWrite, Category = "Reference")
	UResizeComponent* ResizeComponent;

	UPROPERTY(BlueprintReadWrite, Category="Reference")
	USkeletalMeshComponent* SkeletalMeshRef;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reference")
	TSubclassOf<class AActor> SpawnableMorphObject;
};
