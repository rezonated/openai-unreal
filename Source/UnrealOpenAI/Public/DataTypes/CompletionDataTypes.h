// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "CompletionDataTypes.generated.h"

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
	float temperature = 0.f;

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