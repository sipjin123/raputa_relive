#pragma once

#include "CoreMinimal.h"
#include "LoginSubSystem.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSelectPawnIndexChange, const int32, CurrentIndex, const int32, OldIndex);



UCLASS(BlueprintType)
class PROJRELIVE_API ULoginSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable)
	void UpdateSelectPawnIndex(const int32 Index);

	UFUNCTION(BlueprintCallable)
	int32 GetCurrentSelectPawnIndex() const { return SelectedAvatarIndex; }

	UFUNCTION(BlueprintCallable)
	void UpdateSelectedVTuberId(const FString& Id);

	UFUNCTION(BlueprintCallable)
	FString GetSelectedVTuberId() const { return SelectedVTuberId; }

	UFUNCTION(BlueprintCallable)
	FVTuberSpawnPoint GetVTuberSpawnInfoById(const FString& Id) const;

	UPROPERTY(BlueprintAssignable)
	FOnSelectPawnIndexChange OnSelectPawnIndexChange;

private:

	// current choosed pawn Index
	int32 SelectedAvatarIndex = 0;

	// self pawn Show Name setting
	FString SelectedVTuberId;

};
