#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LoginHUD.generated.h"


class ULoginWidget;


/**
 * 
 */
UCLASS()
class PROJRELIVE_API ALoginHUD : public AHUD
{
	GENERATED_BODY()


public:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULoginWidget> LoginWidgetClass = nullptr;

	UPROPERTY()
	TObjectPtr<ULoginWidget> LoginWidget = nullptr;


protected:

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


};
