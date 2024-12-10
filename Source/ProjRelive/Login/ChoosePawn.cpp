#include "ChoosePawn.h"
#include "ProjRelive.h"
#include "Subsystems/LoginSubSystem.h"

#include "Camera/CameraComponent.h"
#include "Camera/CameraActor.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"


//////////////////////////////////////////////////////////////////////////
// AChoosePawn

AChoosePawn::AChoosePawn(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	
	bReplicates = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));

	// Make the scene component the root component
	RootComponent = SceneComponent;

	// Setup camera defaults
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->FieldOfView = 90.0f;
	CameraComponent->bConstrainAspectRatio = true;
	CameraComponent->AspectRatio = 1.777778f;
	CameraComponent->PostProcessBlendWeight = 1.0f;

	CameraComponent->SetupAttachment(SceneComponent);

}

USceneComponent* AChoosePawn::GetDefaultAttachComponent() const
{
	return CameraComponent;
}

void AChoosePawn::OnSelectPawnChange(const int32 NewIndex, const int32 OldIndex)
{
	if (NewIndex >= SelectPawns.Num())
	{
		return;
	}

	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	AActor* DisplaySelectActor = UGameplayStatics::GetActorOfClass(CurrentWorld, SelectPawnClass);
	if (!DisplaySelectActor)
	{
		return;
	}

	FTransform SpawnTransform = DisplaySelectActor->GetTransform();
	DisplaySelectActor->Destroy();

	AActor* SelectActor = Cast<AActor>(UGameplayStatics::BeginDeferredActorSpawnFromClass(
		GetWorld(),
		SelectPawns[NewIndex],
		SpawnTransform,
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn,
		this));

	if (!SelectActor)
	{
		UE_LOG(LogProjRelive, Error, TEXT("%s(): %d Spawn Select Actor Failed"), *FString(__FUNCTION__), __LINE__);
	}

	UGameplayStatics::FinishSpawningActor(SelectActor, SpawnTransform);
}

void AChoosePawn::BeginPlay()
{	
	Super::BeginPlay();

	BindCallBack();
}

void AChoosePawn::BindCallBack()
{
	const UWorld* CurrentWorld = GetWorld();
	if (!CurrentWorld)
	{
		return;
	}

	UGameInstance* GI = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(CurrentWorld));
	if (!GI)
	{
		return;
	}

	ULoginSubSystem* LoginSubSystem = GI->GetSubsystem<ULoginSubSystem>();
	if (!LoginSubSystem)
	{
		return;
	}

	LoginSubSystem->OnSelectPawnIndexChange.AddDynamic(this, &ThisClass::OnSelectPawnChange);

	LoginSubSystem->UpdateSelectPawnIndex(0);
	LoginSubSystem->UpdateSelectedVTuberId("1");

}
