#pragma once

#include "CoreMinimal.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Blueprint/UserWidget.h"
#include "VTuberListEntry.generated.h"

class UTextBlock;
class UBorder;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDataAssigned, FString, VTuberId);
UCLASS(Abstract)
class UVTuberListEntry : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	// IUserObjectListEntry
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;
	// IUserObjectListEntry


	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> VTuberName = nullptr;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UBorder> BackGroundColor = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor SelectedColor;

	UPROPERTY(EditDefaultsOnly)
	FLinearColor UnSelectedColor;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnDataAssigned OnDataAssigned;
};
