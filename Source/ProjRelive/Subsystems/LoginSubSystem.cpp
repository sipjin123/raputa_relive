#include "LoginSubSystem.h"
#include "ProjRelive.h"
#include "Login/LoginController.h"
#include "Login/ChoosePawn.h"

#include "Configuration/ServerConfig.h"

#include "Kismet/GameplayStatics.h"


void ULoginSubSystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	UE_LOG(LogProjRelive, Log, TEXT("%s(): %d Deinitialize ULoginSubSystem GameInstance Subsystem."), *FString(__FUNCTION__), __LINE__);
}

void ULoginSubSystem::Deinitialize()
{
	UE_LOG(LogProjRelive, Log, TEXT("%s(): %d Deinitialize ULoginSubSystem GameInstance Subsystem."), *FString(__FUNCTION__), __LINE__);

	Super::Deinitialize();
}

void ULoginSubSystem::UpdateSelectPawnIndex(const int32 Index)
{
	ALoginController* PC = Cast<ALoginController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		return;
	}

	AChoosePawn* ChoosePawn = Cast<AChoosePawn>(PC->GetPawn());
	if (!ChoosePawn)
	{
		return;
	}

	const int32 NewIndex = Index % ChoosePawn->SelectPawns.Num();

	int32 OldIndex = SelectedAvatarIndex;
	SelectedAvatarIndex = NewIndex;

	OnSelectPawnIndexChange.Broadcast(SelectedAvatarIndex, OldIndex);
}

void ULoginSubSystem::UpdateSelectedVTuberId(const FString& Id)
{
	SelectedVTuberId = Id;
}

FVTuberSpawnPoint ULoginSubSystem::GetVTuberSpawnInfoById(const FString& Id) const
{
	const TArray<FVTuberSpawnPoint>& AllVTubers = UServerConfig::Get().AllVTubers;
	for (auto OneVTuber : AllVTubers)
	{
		if (OneVTuber.VTuberId == Id)
		{
			return OneVTuber;
		}
	}

	return FVTuberSpawnPoint();
}
