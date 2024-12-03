// Copyright WanWanHa NetWork Technology, LLC. All Rights Reserved.


#include "StatusBarWidget.h"

#include "Components/TextBlock.h"


void UStatusBarWidget::UpdateCharacterName(const FString& Name)
{
	if (CharacterName)
	{
		CharacterName->SetText(FText::FromString(Name));
		// 强制刷新 UI
		CharacterName->SynchronizeProperties();
	}
}

void UStatusBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

}
