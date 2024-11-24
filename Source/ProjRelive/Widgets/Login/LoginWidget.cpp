#include "LoginWidget.h"
#include "ProjRelive.h"
#include "ButtonText.h"
#include "Login/LoginController.h"
#include "Subsystems/LoginSubSystem.h"

#include "Configuration/ServerConfig.h"

#include "Kismet/GameplayStatics.h"


void ULoginWidget::OnStartGameBtnClicked()
{
	ALoginController* PC = Cast<ALoginController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
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

	const int32 NewSelectIndex = LoginSubSystem->GetCurrentSelectPawnIndex() + 1;
	LoginSubSystem->UpdateSelectPawnIndex(NewSelectIndex);

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

	if (!StartGameBtn || !SelectAvatarBtn )
	{
		return;
	}

	StartGameBtn->OnClicked.AddDynamic(this, &ThisClass::OnStartGameBtnClicked);
	SelectAvatarBtn->OnClicked.AddDynamic(this, &ThisClass::OnSelectAvatarBtnClicked);
}
