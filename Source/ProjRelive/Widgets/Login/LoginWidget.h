#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"



class UButtonText;


UCLASS()
class PROJRELIVE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void OnStartGameBtnClicked();

	UFUNCTION()
	void OnSelectAvatarBtnClicked();


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButtonText> StartGameBtn = nullptr;	    // 开始游戏

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButtonText> SelectAvatarBtn = nullptr;		// 选择 avatar

protected:

	virtual void NativeConstruct() override;


};
