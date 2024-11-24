#include "ButtonText.h"

#include "Components/TextBlock.h"
#include "Components/Button.h"

void UButtonText::OnButtonClicked()
{
	OnClicked.Broadcast();
}

void UButtonText::OnButtonHovered()
{
	OnHovered.Broadcast();
}

void UButtonText::OnButtonUnhovered()
{
	OnUnHovered.Broadcast();
}

void UButtonText::Disable()
{
	if (!Button)
	{
		return;
	}

	Button->SetIsEnabled(false);
}

void UButtonText::Enable()
{
	if (!Button)
	{
		return;
	}

	Button->SetIsEnabled(true);
}

void UButtonText::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Button)
	{
		return;
	}

	Button->OnReleased.AddDynamic(this, &ThisClass::OnButtonClicked);
	Button->OnHovered.AddDynamic(this, &ThisClass::OnButtonHovered);
	Button->OnUnhovered.AddDynamic(this, &ThisClass::OnButtonUnhovered);
}

void UButtonText::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ButtonTextLabel)
	{
		ButtonTextLabel->SetText(FText::FromString(ButtonText));
	}

	if (Button)
	{
		Button->SetBackgroundColor(ButtonBGColor);
	}
}
