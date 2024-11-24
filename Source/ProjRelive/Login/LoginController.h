#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LoginController.generated.h"


class AChoosePawn;


/**
 * 
 */
UCLASS()
class PROJRELIVE_API ALoginController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ALoginController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


protected:

	virtual void BeginPlay() override;

};
