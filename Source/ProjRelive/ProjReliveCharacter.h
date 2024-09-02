// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Enums/EPlayerStats.h"
#include "Enums/PlayerCombatState.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
//#include "Player/RelivePlayerController.h"
#include "ProjReliveCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLookAtComplete);
DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AProjReliveCharacter : public ACharacter
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
protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
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

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	EPowerupType CurrentPowerup;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Stats")
	int CurrentAbilityId;
	
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
	
	UPROPERTY(BlueprintReadWrite, Category="Rotation")
	bool IsDead;
	
	UPROPERTY(BlueprintReadWrite, Category="Reference")
	FVector TargetClickedLocation;
};

