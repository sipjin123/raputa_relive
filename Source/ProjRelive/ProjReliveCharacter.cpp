// Copyright Epic Games, Inc. All Rights Reserved.

#include "ProjReliveCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Player/RelivePlayerController.h"
#include "RelivePlayerState.h"
#include "Widgets/World/StatusBarWidget.h"
#include "Subsystems/LoginSubSystem.h"

#include "Configuration/ServerConfig.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerState.h"

#include "ActorComponents/MorphComponent.h"
#include "ActorComponents/PlayerModifierComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystemComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AProjReliveCharacter

AProjReliveCharacter::AProjReliveCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	
	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("CameraRoot"));
	CameraRoot->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraRoot); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	//FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named ThirdPersonCharacter (to avoid direct content references in C++)

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	// Moved Name to Stat Widget
	/*
	StatusBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("StatusBarComponent"));
	StatusBarComponent->SetIsReplicated(true);
	StatusBarComponent->SetupAttachment(RootComponent);*/
	//StatusBarComponent = GetComponentByClass<UWidgetComponent>();
}

void AProjReliveCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AProjReliveCharacter, PowerupQuantity);
	DOREPLIFETIME(AProjReliveCharacter, CurrentPowerup);
	DOREPLIFETIME(AProjReliveCharacter, PlayerTargetLocation);
	DOREPLIFETIME(AProjReliveCharacter, IsDead);
	DOREPLIFETIME(AProjReliveCharacter, IsUsingAbility);
	DOREPLIFETIME(AProjReliveCharacter, CanMove);
	DOREPLIFETIME(AProjReliveCharacter, TeamId);
	DOREPLIFETIME(AProjReliveCharacter, ShowTeamIndicator);
	DOREPLIFETIME(AProjReliveCharacter, PlayerIndex);
	DOREPLIFETIME(AProjReliveCharacter, IsMovingToPoint);
	DOREPLIFETIME(AProjReliveCharacter, IsHost);
	DOREPLIFETIME(AProjReliveCharacter, IsNotTargetable);
}

void AProjReliveCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	if (GetOwner())
	{
		// Assign on Blueprint to reference its Blueprint Counterpart
		MorphComponent = GetOwner()->FindComponentByClass<UMorphComponent>();
		PlayerModifierComponent = GetOwner()->FindComponentByClass<UPlayerModifierComponent>();
		UE_LOG(LogTemp, Warning, TEXT("Components Finished setting up"));
	}

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void AProjReliveCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void AProjReliveCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

}

void AProjReliveCharacter::UpdateCharacterSelfUI(const FString& NewName)
{
	OnCharVTuberNameAssigned.Broadcast(NewName);
	// Moved Name to Stat Widget
	/*
	if (!IsValid(StatusBarComponent))
	{
		return;
	}

	UStatusBarWidget* StatusBar = Cast<UStatusBarWidget>(StatusBarComponent->GetWidget());
	if (!StatusBar)
	{
		return;
	}

	StatusBar->UpdateCharacterName(NewName);*/
}

void AProjReliveCharacter::OnRep_TeamId()
{
	OnTeamChanged.Broadcast();
}

void AProjReliveCharacter::OnRep_SetHost()
{
	OnHostDeclared.Broadcast();
}

FUniqueNetIdRepl AProjReliveCharacter::GetPlayerID()
{
	if (GetPlayerState()) {
		auto MyPlayerState = Cast<APlayerState>(GetPlayerState());
		return GetPlayerState()->UniqueId;
	}
	return FUniqueNetIdRepl();
}

//////////////////////////////////////////////////////////////////////////
// Input

void AProjReliveCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		//EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AProjReliveCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AProjReliveCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AProjReliveCharacter::Move(const FInputActionValue& Value)
{
	if (FreezeInput || !CanMove)
	{
		return;
	}
	
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		if (IsMovingToPoint) {
			if (FMath::Abs(MovementVector.X) > 0 || FMath::Abs(MovementVector.Y) > 0) {
				IsMovingToPoint = false;
				OnMovementOverride.Broadcast();
			}
		}

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AProjReliveCharacter::Look(const FInputActionValue& Value)
{
	if (FreezeInput)
	{
		return;
	}
	
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		//AddControllerYawInput(LookAxisVector.X);
		//AddControllerPitchInput(LookAxisVector.Y);
	}
}