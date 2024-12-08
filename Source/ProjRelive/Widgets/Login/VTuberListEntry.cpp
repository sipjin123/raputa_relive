#include "VTuberListEntry.h"
#include "Widgets/Login/LoginWidget.h"
#include "Subsystems/LoginSubSystem.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Kismet/GameplayStatics.h"


void UVTuberListEntry::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);

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

	UVTuberInfoData* pInfo = Cast<UVTuberInfoData>(ListItemObject);
	if (!pInfo || !VTuberName)
	{
		return;
	}

	VTuberName->SetText(FText::FromString(pInfo->VTuberName));

	if (pInfo->VTuberId == LoginSubSystem->GetSelectedVTuberId())
	{
		BackGroundColor->SetBrushColor(SelectedColor);
	}
	else
	{
		BackGroundColor->SetBrushColor(UnSelectedColor);
	}
}
