// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "CompletionDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FCreateCompletionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	FString prompt = "<|endoftext|>";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	FString suffix;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	int max_tokens = 1000;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	float temperature = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	float top_p = 1.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	int n = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	bool stream = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	int logprobs = 5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	bool echo = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	FString stop;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	float presence_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	float frequency_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	int best_of = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	TMap<FString, FString> logit_bias;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Request")
	FString user;
};

USTRUCT(BlueprintType)
struct FCreateCompletionResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	int32 created {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	TArray<FChoice> choices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "OpenAI | Create Completion Response")
	FUsage usage;
};