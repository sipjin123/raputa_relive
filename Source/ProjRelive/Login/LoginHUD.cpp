#include "LoginHUD.h"
#include "Widgets/Login/LoginWidget.h"

#include "Kismet/GameplayStatics.h"


void ALoginHUD::BeginPlay()
{
	Super::BeginPlay();

	if (!LoginWidgetClass || LoginWidget)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PC)
	{
		return;
	}
	PC->bShowMouseCursor = true;
	PC->bEnableClickEvents = true;
	PC->bEnableMouseOverEvents = true;
	PC->SetInputMode(FInputModeUIOnly());

	LoginWidget = CreateWidget<ULoginWidget>(PC, LoginWidgetClass);
	LoginWidget->AddToViewport();
	LoginWidget->SetVisibility(ESlateVisibility::Visible);
}

void ALoginHUD::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}