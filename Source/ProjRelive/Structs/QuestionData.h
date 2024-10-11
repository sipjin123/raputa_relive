// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "QuestionData.generated.h"

/**
 * 
 */

USTRUCT(Blueprintable)
struct FQuestionTableData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Question Data")
	int32 Id = -1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question Data", meta = (UIMin = 1, UIMax = 100))
	FString QuestionText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Question Data")
	int32 RewardPoints = -1;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Question Data")
	int32 CorrectAnswer = -1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Question Data", meta = (UIMin = 1, UIMax = 100))
	TArray<FString> AnswersText;
};

/*
USTRUCT(BlueprintType)
struct FQuestionData
{
	GENERATED_BODY()
public:

	FQuestionData()
	{

	}
};*/