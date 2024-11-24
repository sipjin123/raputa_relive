#include "LoginController.h"

// UE
#include "Camera/CameraActor.h"
#include "Kismet/GameplayStatics.h"



ALoginController::ALoginController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
}

void ALoginController::BeginPlay()
{
	Super::BeginPlay();
}
