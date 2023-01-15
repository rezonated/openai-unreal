// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "Constants/ModerationConstants.h"
#include "Enums/ModerationEnums.h"
#include "ModerationDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FModerationResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool flagged;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, bool> categories;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, float> category_scores;
};


USTRUCT(BlueprintType)
struct FCreateModerationRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model = ModerationModels[static_cast<int>(EModerationModels::EMM_Stable)];
};


USTRUCT(BlueprintType)
struct FCreateModerationResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FModerationResult> results;
};

