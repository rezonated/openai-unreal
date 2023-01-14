#pragma once
#include "CoreMinimal.h"
#include "DataTypes.generated.h"

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int index;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString finish_reason;
};

USTRUCT(BlueprintType)
struct FUsage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString completion_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString total_tokens;
};

USTRUCT(BlueprintType)
struct FCreateCompletionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt = "<|endoftext|>";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString suffix;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int max_tokens = 1000;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float temperature = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float top_p = 1.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int n = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool stream = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs = 5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool echo = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString stop;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float presence_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float frequency_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int best_of = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, FString> logit_bias;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString user;
};

USTRUCT(BlueprintType)
struct FCreateCompletionResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FChoice choices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUsage usage;
};