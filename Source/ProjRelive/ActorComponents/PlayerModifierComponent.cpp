// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerModifierComponent.h"
#include "MorphComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UPlayerModifierComponent::UPlayerModifierComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerModifierComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	UE_LOG(LogTemp, Log, TEXT("Player Stat Comp Begin"));
}

void UPlayerModifierComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UPlayerModifierComponent, AppliedBuffs);
	DOREPLIFETIME(UPlayerModifierComponent, AppliedDebuffs);
	DOREPLIFETIME(UPlayerModifierComponent, CurrentBuffTimer);
}

// Called every frame
void UPlayerModifierComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UPlayerModifierComponent::Server_ApplyBuff_Implementation(EBuffs BuffToApply)
{
	// Try to find existing buff
	FBuffState* FoundEntry = AppliedBuffs.FindByPredicate([BuffToApply](const FBuffState& InBuffState)
		{
			return InBuffState.Buff == BuffToApply;
		});

	FString DisplayEnum = *UEnum::GetDisplayValueAsText(BuffToApply).ToString();
	if (!FoundEntry) {
		UE_LOG(LogTemp, Log, TEXT("Failed to Find an Existing Buff:{%s}, Adding New One"), *DisplayEnum);
		
		FBuffState NewBuffState;
		NewBuffState.Buff = BuffToApply;
		NewBuffState.Duration = 3.0f;
		NewBuffState.DateTimeCasted = FDateTime::Now();

		AppliedBuffs.Add(NewBuffState);
		NetMulticast_ExecuteBuff_Implementation(BuffToApply);

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Found an Existing Buff:{%s}"), *DisplayEnum);
	}
}

bool UPlayerModifierComponent::Server_ApplyBuff_Validate(EBuffs BuffToApply)
{
	return true;
}

void UPlayerModifierComponent::NetMulticast_ExecuteBuff_Implementation(EBuffs BuffToApply)
{
	// Do Client Logic Here
	OnBuffApplied.Broadcast(BuffToApply);
	ProcessBuffEffect(BuffToApply);
}

void UPlayerModifierComponent::ProcessBuffEffect(EBuffs BuffToApply)
{
	switch (BuffToApply)
	{
	case EBuffs::None:
		break;
	case EBuffs::Speedup: {
		}
		break;
	case EBuffs::Shielded: {
		}
		break;
	case EBuffs::Invulnerable: {
		}
		break;
	case EBuffs::Invisible: {
		}
		break;
	default:
		break;
	}
}

void UPlayerModifierComponent::Server_ApplyDebuff_Implementation(EDebuffs DebuffToApply)
{	
	// Try to find existing buff
	FDebuffState* FoundEntry = AppliedDebuffs.FindByPredicate([DebuffToApply](const FDebuffState& InDebuffState)
		{
			return InDebuffState.Debuff == DebuffToApply;
		});

	FString DisplayEnum = *UEnum::GetDisplayValueAsText(DebuffToApply).ToString();
	if (!FoundEntry) {
		UE_LOG(LogTemp, Log, TEXT("Failed to Find an Existing Buff:{%s}, Adding New One"), *DisplayEnum);

		FDebuffState NewDebuffState;
		NewDebuffState.Debuff = DebuffToApply;
		NewDebuffState.Duration = 3.0f;
		NewDebuffState.DateTimeCasted = FDateTime::Now();

		AppliedDebuffs.Add(NewDebuffState);
		NetMulticast_ExecuteDebuff_Implementation(DebuffToApply);

	}
	else {
		UE_LOG(LogTemp, Log, TEXT("Found an Existing Buff:{%s}"), *DisplayEnum);
	}
}

bool UPlayerModifierComponent::Server_ApplyDebuff_Validate(EDebuffs DebuffToApply)
{
	return true;
}

void UPlayerModifierComponent::NetMulticast_ExecuteDebuff_Implementation(EDebuffs DebuffToApply)
{
	// Do Client Logic Here
	OnDebuffApplied.Broadcast(DebuffToApply);
	ProcessDebuffEffect(DebuffToApply);
}

void UPlayerModifierComponent::ProcessDebuffEffect(EDebuffs DebuffToApply)
{
	switch (DebuffToApply)
	{
	case EDebuffs::Morphed: {
			UMorphComponent* MorphComp = GetOwner()->FindComponentByClass<UMorphComponent>();
			MorphComp->ApplyMorphEffect();
		}
		break;
	case EDebuffs::Stunned: {
		}
		break;
	case EDebuffs::Slowed: {
		}
		break;
	}
}
