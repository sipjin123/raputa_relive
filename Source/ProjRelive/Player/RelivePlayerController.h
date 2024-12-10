// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjRelive/ProjReliveCharacter.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "RelivePlayerController.generated.h"


class AProjReliveCharacter;
class APlayerSpawnPoint;
struct FDonatePlayerInfo;


/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPossessAcknowledge);

UCLASS()
class PROJRELIVE_API ARelivePlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARelivePlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	// Tell All client get Donation
	UFUNCTION(Client, Reliable)
	void Client_ReceiveDonation(const FDonatePlayerInfo& DonateInfo);

	UFUNCTION(Client, Reliable)
	void Client_CanSpawnAvatar();

	UFUNCTION(Server, Reliable)
	void Server_ReqSpawnAvatar(const int32 SpawnPosIndex, const int32 AvatarIndex, const FString& ID);
	
	UPROPERTY(BlueprintReadWrite, Category="References")
	AActor* ReliveCharacter;
	
	UPROPERTY(BlueprintReadWrite, Category="References")
	AActor* CurrentTargetActor;

	UPROPERTY(BlueprintReadWrite, Category="References")
	FVector ClickedLocation;
	
	UPROPERTY(BlueprintReadWrite, Category="Stats")
	float ZoomSpeed = 3.f;

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnPossessAcknowledge OnPossessAcknowledge;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<int32, TSubclassOf<AProjReliveCharacter>> SpawnCharacterPair;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<APlayerSpawnPoint> SpawnPointClass = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = "Stats")
	bool IsMouseOnHold;

protected:
	virtual void AcknowledgePossession(APawn* P) override;

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	// 所有的出生点 类型是 APlayerSpawnPoint
	TArray<AActor*> AllSpawnPoints;


};
