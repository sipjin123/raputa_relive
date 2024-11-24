#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "LoginGameMode.generated.h"


class ALoginController;
class UChooseConfigManager;

/**
 * UI 选择 场景相关  是 standalone 的模式
 */
UCLASS()
class PROJRELIVE_API ALoginGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ALoginGameMode(const FObjectInitializer& ObjectInitializer);


};
