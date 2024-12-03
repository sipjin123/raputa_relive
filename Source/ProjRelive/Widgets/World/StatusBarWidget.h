// Copyright WanWanHa NetWork Technology, LLC. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBarWidget.generated.h"

class UTextBlock;

/**
 * display player character status in UI
 */
UCLASS()
class PROJRELIVE_API UStatusBarWidget : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION(BlueprintCallable)
	void UpdateCharacterName(const FString& Name);

	UPROPERTY(BlueprintReadWrite, Category = ">Tips", Meta = (BindWidget))
	TObjectPtr<UTextBlock> CharacterName;		// name of character


protected:

	virtual void NativeConstruct() override;



};
