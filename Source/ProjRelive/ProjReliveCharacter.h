// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemInterface.h"

#include "Enums/EPlayerStats.h"
#include "Enums/PlayerCombatState.h"

#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "ProjReliveCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTeamChanged);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnHostDeclared);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMovementOverride);
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS()
//UCLASS(config=Game)
class AProjReliveCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** Follow camera root */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USceneComponent* CameraRoot;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

public:
	AProjReliveCharacter();
	
	UPROPERTY(BlueprintAssignable, BlueprintCallable, BlueprintReadWrite)
	FOnLookAtComplete OnLookAtComplete;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UPlayerModifierComponent* PlayerModifierComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	class UMorphComponent* MorphComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GAS", meta = (AllowPrivateAccess = "true"))
	class UAbilitySystemComponent* AbilitySystemComponent;

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return  AbilitySystemComponent;
	}

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// To add mapping context
	virtual void BeginPlay();

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	FGameplayTagContainer TagContainer;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats", ReplicatedUsing = OnRep_TeamId)
	int TeamId;
	UFUNCTION()
	void OnRep_TeamId();
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	bool ShowTeamIndicator;

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	int PlayerIndex;

	//UPROPERTY(BlueprintReadWrite, Category = "Stats")
	//FUniqueNetIdRepl PlayerID;
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FUniqueNetIdRepl GetPlayerID();

	UPROPERTY(BlueprintReadWrite, Replicated, Category="Stats")
	EPowerupType CurrentPowerup;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	int PowerupQuantity;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats")
	bool IsUsingAbility;
	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Stats", ReplicatedUsing = OnRep_SetHost)
	bool IsHost;
	UFUNCTION()
	void OnRep_SetHost();

	UPROPERTY(BlueprintReadWrite, Replicated, Category = "Controls")
	bool IsMovingToPoint;
	UPROPERTY(BlueprintReadWrite, Category="Controls")
	bool FreezeInput;
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	bool ShouldLookAtTarget;
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	float LookAtLerp = 0;
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	float LookAtSpeed = 3;
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	float LookAtTimer = 0;
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	FRotator InitialRotation;
	
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Rotation")
	bool IsDead;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "Movement")
	bool CanMove = true;
	UPROPERTY(BlueprintReadWrite, Category = "Movement")
	bool IsHoldingCtrl = false;
	
	UPROPERTY(BlueprintReadWrite, Category="Reference")
	FVector TargetClickedLocation;
	UPROPERTY(Replicated, BlueprintReadWrite, Category="Reference")
	FVector PlayerTargetLocation;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnTeamChanged OnTeamChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnHostDeclared OnHostDeclared;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnMovementOverride OnMovementOverride;

	UPROPERTY(BlueprintReadWrite)
	AActor* ActorTarget;
};

