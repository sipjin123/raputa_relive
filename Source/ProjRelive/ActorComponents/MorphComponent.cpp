// Fill out your copyright notice in the Description page of Project Settings.


#include "MorphComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UMorphComponent::UMorphComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UMorphComponent::BeginPlay()
{
	Super::BeginPlay();
	if (GetOwner()) {
		ACharacter* CharRef = Cast<ACharacter>(GetOwner());
		if (CharRef != nullptr) {
			SkeletalMeshRef = CharRef->GetMesh();
		}
		ResizeComponent = GetOwner()->FindComponentByClass<UResizeComponent>();
	}
}


// Called every frame
void UMorphComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMorphComponent::ApplyMorphEffect()
{
	ACharacter* CharRef = Cast<ACharacter>(GetOwner());
	if (CharRef != nullptr) {
		//ResizeComponent->Shrink(false);
		SkeletalMeshRef = CharRef->GetMesh();
		SkeletalMeshRef->SetVisibility(false);

		SpawnedActorRef = GetWorld()->SpawnActor<AActor>(SpawnableMorphObject, CharRef->GetActorTransform());
		//GetWorld()->SpawnActor<AProjectile>(Location, Rotation, SpawnInfo);
	}
}

void UMorphComponent::ReleaseMorphEffect()
{
	ACharacter* CharRef = Cast<ACharacter>(GetOwner());
	if (CharRef != nullptr) {
		if (SpawnedActorRef) {
			SpawnedActorRef->Destroy();
		}
		SkeletalMeshRef = CharRef->GetMesh();
		SkeletalMeshRef->SetVisibility(true);
		//ResizeComponent->Enlarge(false);
	}
}

