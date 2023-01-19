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
	
	TOptional<int> max_tokens = 1000;
	
	TOptional<float> temperature = 0.f;
	
	TOptional<float> top_p = 1.f;
	
	TOptional<int> n = 1;

	TOptional<bool> stream = false;
	
	TOptional<int> logprobs = 5;
	
	TOptional<bool> echo = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString stop;
	
	TOptional<float> presence_penalty = 0.f;
	
	TOptional<float> frequency_penalty = 0.f;
	
	TOptional<int> best_of = 1;

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