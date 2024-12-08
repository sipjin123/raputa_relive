#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"



class UListView;
class UEditableTextBox;
class UButtonText;


UCLASS(Blueprintable)
class UVTuberInfoData : public UObject
{
	GENERATED_BODY()

public:

	void Reset()
	{
		VTuberId = "";
		VTuberName = "";
		SpawnIndex = -1;
	}

	FString VTuberId = "";
	FString VTuberName = "";
	int32  SpawnIndex = -1;
};

UCLASS()
class PROJRELIVE_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION()
	void OnStartGameBtnClicked();

	UFUNCTION()
	void OnSelectAvatarBtnClicked();

	UPROPERTY(EditDefaultsOnly, Category = ">Widgets", Meta = (BindWidget))
	TObjectPtr<UListView> VTuberInfoList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButtonText> StartGameBtn;	    // 开始游戏

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (BindWidget))
	TObjectPtr<UButtonText> SelectAvatarBtn;		// 选择 avatar

protected:

	virtual void NativeConstruct() override;

	/*
	* 当选中 某一个 VTuber 
	*/
	void OnSelectedSpecifyVTuber(UObject* OneVTuber);


private:

	void BindBtnCallback();

	void InitVTuberInfo();

	TArray<UVTuberInfoData*> AllVTuberInfos;
};
