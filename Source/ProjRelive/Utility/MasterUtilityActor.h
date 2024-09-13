// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjRelive/Core/ReliveActor.h"
#include "MasterUtilityActor.generated.h"

/**
 * 
 */
UCLASS()
class PROJRELIVE_API AMasterUtilityActor : public AReliveActor
{
	GENERATED_BODY()
public:
	AMasterUtilityActor();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	/*
	// Called by Client, Processed on Sever
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_ApplySomething();
	void Server_ApplySomething_Implementation();

	// Executed by Server, Only Sends to Local Client
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_DoSomething();

	// Executed by Server, Sends to All Clients
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void NetMulticast_CallOnAllClient();*/
};

// This allows breaking of variable fetched in blueprint
//USTRUCT(Blueprintable)
//struct FItemData
//BlueprintReadWrite
//INT Sample 