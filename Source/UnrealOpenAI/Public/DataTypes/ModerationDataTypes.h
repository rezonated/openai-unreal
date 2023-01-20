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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	bool flagged;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	TMap<FString, bool> categories;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	TMap<FString, float> category_scores;
};


USTRUCT(BlueprintType)
struct FCreateModerationRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Request")
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Request")
	FString model = ModerationModels[static_cast<int>(EModerationModels::EMM_Stable)];
};


USTRUCT(BlueprintType)
struct FCreateModerationResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Response")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Response")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Response")
	TArray<FModerationResult> results;
};

