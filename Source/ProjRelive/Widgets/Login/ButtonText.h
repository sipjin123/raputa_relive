#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ButtonText.generated.h"


class UButton;
class UTextBlock;


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonClicked);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonHovered);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnButtonUnhovered);


/**
 *  UI 里面需要用的 Button , 重写一个
 */
UCLASS()
class PROJRELIVE_API UButtonText : public UUserWidget
{
	GENERATED_BODY()
	

public:

	UFUNCTION()
	void OnButtonClicked();

	UFUNCTION()
	void OnButtonHovered();

	UFUNCTION()
	void OnButtonUnhovered();

	UFUNCTION(BlueprintCallable)
	void Disable();

	UFUNCTION(BlueprintCallable)
	void Enable();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ButtonText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FColor ButtonBGColor;

	UPROPERTY(EditAnywhere, Meta = (BindWidget))
	TObjectPtr<UButton> Button = nullptr;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<UTextBlock> ButtonTextLabel = nullptr;

	UPROPERTY(BlueprintAssignable, Category = "ButtonText")
	FOnButtonClicked OnClicked;

	UPROPERTY(BlueprintAssignable, Category = "ButtonText")
	FOnButtonClicked OnHovered;

	UPROPERTY(BlueprintAssignable, Category = "ButtonText")
	FOnButtonClicked OnUnHovered;

protected:

	virtual void NativeConstruct() override;
	virtual void NativePreConstruct() override;


};
