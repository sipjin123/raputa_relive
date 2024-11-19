// Fill out your copyright notice in the Description page of Project Settings.


#include "ResizeComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UResizeComponent::UResizeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UResizeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	RegisterOriginScale();
}

void UResizeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UResizeComponent, IsResizing);
	DOREPLIFETIME(UResizeComponent, ResizeState);
	DOREPLIFETIME(UResizeComponent, DestroyOnEnd);
	DOREPLIFETIME(UResizeComponent, OriginScale);
	DOREPLIFETIME(UResizeComponent, HideOnEnd);
	DOREPLIFETIME(UResizeComponent, UseMeshOnly);
}


// Called every frame
void UResizeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UResizeComponent::Server_Enlarge_Implementation(bool ShouldDestroyOnEnd)
{
	NetMulti_Enlarge(ShouldDestroyOnEnd);
}

void UResizeComponent::NetMulti_Enlarge_Implementation(bool ShouldDestroyOnEnd)
{
	Enlarge(ShouldDestroyOnEnd);
}

void UResizeComponent::Enlarge(bool ShouldDestroyOnEnd)
{
	DestroyOnEnd = ShouldDestroyOnEnd;
	ResizeState = EResizeState::Enlarging;
	EnlargeLerpVal = 0.f;
	IsResizing = true;
	OnEnlarge.Broadcast();
}

void UResizeComponent::Server_Shrink_Implementation(bool ShouldDestroyOnEnd)
{
	NetMulti_Shrink(ShouldDestroyOnEnd);
}

void UResizeComponent::NetMulti_Shrink_Implementation(bool ShouldDestroyOnEnd)
{
	Shrink(ShouldDestroyOnEnd);
}

void UResizeComponent::Shrink(bool ShouldDestroyOnEnd)
{
	DestroyOnEnd = ShouldDestroyOnEnd;
	ResizeState = EResizeState::Shrinking;
	StrinkLerpVal = 0.f;
	IsResizing = true;
	OnShrink.Broadcast();
}

void UResizeComponent::OverrideShrinkSpeed(float NewSpeed)
{
	ShrinkSpeed = NewSpeed;
}

void UResizeComponent::OverrideEnlargeSpeed(float NewSpeed)
{
	EnlargeSpeed = NewSpeed;
}

void UResizeComponent::FinishResizing()
{
	ResizeState = EResizeState::None;
	//StrinkLerpVal = 0.f;
	IsResizing = false;
	OnFinishResize.Broadcast();
}

void UResizeComponent::ResetScale()
{
	if (GetOwner()) {
		GetOwner()->SetActorScale3D(OriginScale);
	}
}

void UResizeComponent::ResetVariables()
{
	OnResetVariables.Broadcast();
}

void UResizeComponent::RegisterOriginScale()
{
	if (GetOwner()) {
		OriginScale = GetOwner()->GetActorScale();
	}
}

bool UResizeComponent::IsShrinking()
{
	return ResizeState == EResizeState::Shrinking;
}

bool UResizeComponent::IsEnlarging()
{
	return ResizeState == EResizeState::Enlarging;
}

bool UResizeComponent::CanResize()
{
	return ResizeState == EResizeState::None;
}

