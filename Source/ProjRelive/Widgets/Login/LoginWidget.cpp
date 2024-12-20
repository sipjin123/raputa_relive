#include "LoginWidget.h"
#include "ProjRelive.h"
#include "ButtonText.h"
#include "Login/LoginController.h"
#include "Subsystems/LoginSubSystem.h"

#include "Configuration/ServerConfig.h"

#include "Components/EditableTextBox.h"
#include "Components/ListView.h"
#include "Kismet/GameplayStatics.h"


void ULoginWidget::OnStartGameBtnClicked()
{
	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (!GI)
	{
		return;
	}

	ALoginController* PC = Cast<ALoginController>(UGameplayStatics::GetPlayerController(CurrentWorld, 0));
	if (!PC)
	{
		return;
	}

	FString URL = FString::Printf(TEXT("%s:%d"), *UServerConfig::GetDedicatedServerIP(), UServerConfig::GetDedicatedServerPort());

	PC->ClientTravel(URL, ETravelType::TRAVEL_Absolute);
}

void ULoginWidget::OnSelectAvatarBtnClicked()
{
	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	const int32 NewSelectedAvatarIndex = LoginSubSystem->GetCurrentSelectPawnIndex() + 1;
	LoginSubSystem->UpdateSelectPawnIndex(NewSelectedAvatarIndex);
	ALoginController* PC = Cast<ALoginController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (!PC)
	{
		return;
	}

	FString URL = FString::Printf(TEXT("%s:%d"), *UServerConfig::GetDedicatedServerIP(), UServerConfig::GetDedicatedServerPort());
	UE_LOG(LogProjRelive, Error, TEXT("%s(): %d URL: %s"), *FString(__FUNCTION__), __LINE__, *URL);

}

void ULoginWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BindBtnCallback();

	InitVTuberInfo();
}

void ULoginWidget::OnSelectedSpecifyVTuber(UObject* OneVTuber)
{
	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	UVTuberInfoData* SelectedVT = Cast<UVTuberInfoData>(OneVTuber);
	if (!SelectedVT || !VTuberInfoList || !VTuberInfoList2 || !VTuberInfoList3)
	{
		return;
	}

	LoginSubSystem->UpdateSelectedVTuberId(SelectedVT->VTuberId);

	OnAvatarClicked.Broadcast(SelectedVT->VTuberId);
	InitVTuberInfo();
}

void ULoginWidget::BindBtnCallback()
{
	check(VTuberInfoList && VTuberInfoList2 && VTuberInfoList3 && StartGameBtn && SelectAvatarBtn);

	VTuberInfoList->OnItemSelectionChanged().AddUObject(this, &ULoginWidget::OnSelectedSpecifyVTuber);
	VTuberInfoList2->OnItemSelectionChanged().AddUObject(this, &ULoginWidget::OnSelectedSpecifyVTuber);
	VTuberInfoList3->OnItemSelectionChanged().AddUObject(this, &ULoginWidget::OnSelectedSpecifyVTuber);
	StartGameBtn->OnClicked.AddDynamic(this, &ThisClass::OnStartGameBtnClicked);
	SelectAvatarBtn->OnClicked.AddDynamic(this, &ThisClass::OnSelectAvatarBtnClicked);
}

void ULoginWidget::InitVTuberInfo()
{
	AllVTuberInfos.Empty();
	AllVTuberInfos2.Empty();
	AllVTuberInfos3.Empty();

	int i = 0;
	for (auto OneVTuber : UServerConfig::Get().AllVTubers)
	{
		UVTuberInfoData* TempVTuberData = NewObject<UVTuberInfoData>();
		TempVTuberData->VTuberId = OneVTuber.VTuberId;
		TempVTuberData->VTuberName = OneVTuber.VTuberName;
		TempVTuberData->SpawnIndex = OneVTuber.SpawnIndex;
		if (i < 4) {
			AllVTuberInfos.Add(TempVTuberData);
		}
		else if (i < 8) {
			AllVTuberInfos2.Add(TempVTuberData);
		}
		else {
			AllVTuberInfos3.Add(TempVTuberData);
		}
		i++;
	}

	VTuberInfoList->ClearListItems();
	VTuberInfoList->SetListItems(AllVTuberInfos);
	VTuberInfoList->RegenerateAllEntries();

	VTuberInfoList2->ClearListItems();
	VTuberInfoList2->SetListItems(AllVTuberInfos2);
	VTuberInfoList2->RegenerateAllEntries();

	VTuberInfoList3->ClearListItems();
	VTuberInfoList3->SetListItems(AllVTuberInfos3);
	VTuberInfoList3->RegenerateAllEntries();
}
