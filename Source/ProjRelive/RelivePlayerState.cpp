// Fill out your copyright notice in the Description page of Project Settings.


#include "RelivePlayerState.h"
#include "ProjReliveCharacter.h"
#include "Subsystems/LoginSubSystem.h"

#include "Configuration/ServerConfig.h"


#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"

ARelivePlayerState::ARelivePlayerState()
{
}

void ARelivePlayerState::UpdateCharacterName_Implementation(const FString& ID)
{
	APlayerController* PS = Cast<APlayerController>(GetOwner());
	if (!PS)
	{
		return;
	}
	AProjReliveCharacter* OtherCharacter = Cast<AProjReliveCharacter>(PS->GetPawn());
	if (!OtherCharacter)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	OtherCharacter->UpdateCharacterSelfUI(LoginSubSystem->GetVTuberSpawnInfoById(ID).VTuberName);
}

void ARelivePlayerState::BeginPlay()
{
	Super::BeginPlay();
}

void ARelivePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARelivePlayerState, CooldownData);
	DOREPLIFETIME(ARelivePlayerState, PlayerIndex);
	DOREPLIFETIME(ARelivePlayerState, VTuberID);
}

void ARelivePlayerState::OnRep_VTuberID(FString OldID)
{
	APlayerController* PS = Cast<APlayerController>(GetOwner());
	if (!PS)
	{
		return;
	}

	AProjReliveCharacter* SelfCharacter = Cast<AProjReliveCharacter>(PS->GetPawn());
	if (!SelfCharacter)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	SelfCharacter->UpdateCharacterSelfUI(LoginSubSystem->GetVTuberSpawnInfoById(VTuberID).VTuberName);
}
