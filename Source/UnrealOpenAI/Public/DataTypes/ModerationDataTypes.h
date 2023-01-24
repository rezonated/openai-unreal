// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "Constants/ModerationConstants.h"
#include "Enums/ModerationEnums.h"
#include "ModerationDataTypes.generated.h"

// Struct to hold a single moderation result
USTRUCT(BlueprintType)
struct FModerationResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	bool flagged {false};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	TMap<FString, bool> categories;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Moderation Result")
	TMap<FString, float> category_scores;
};

// Struct to construct create moderation request as JSON, described in:
// https://beta.openai.com/docs/api-reference/moderation/create
USTRUCT(BlueprintType)
struct FCreateModerationRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Request")
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Moderation Request")
	FString model = ModerationModels[static_cast<int>(EModerationModels::EMM_Stable)];
};

// Struct to construct create moderation response as JSON, described in:
// https://beta.openai.com/docs/api-reference/moderation/create
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

