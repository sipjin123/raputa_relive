#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ChoosePawn.generated.h"


class UInputAction;


UCLASS(config = Game)
class PROJRELIVE_API AChoosePawn : public APawn
{
	GENERATED_UCLASS_BODY()


public:
	//~ Begin UObject Interface
	virtual class USceneComponent* GetDefaultAttachComponent() const override;
	//~ End UObject Interface

	/** Returns CameraComponent subobject **/
	class UCameraComponent* GetCameraComponent() const { return CameraComponent; }

	UFUNCTION()
	void OnSelectPawnChange(const int32 NewIndex, const int32 OldIndex);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<AActor>> SelectPawns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AActor> SelectPawnClass = nullptr;

protected:

	//~ Begin AActor Interface
	virtual void BeginPlay() override;
	//~ End AActor Interface

private:

	// 根据当前的 选择的index 进行修改
	void BindCallBack();

	/** The camera component for this camera */
	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UCameraComponent> CameraComponent;

	UPROPERTY(Category = CameraActor, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class USceneComponent> SceneComponent;

};
