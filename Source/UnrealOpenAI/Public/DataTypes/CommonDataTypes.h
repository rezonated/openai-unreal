﻿// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.generated.h"

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
struct FFileToLoad
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<uint8> FileData;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString FileName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString FileExtension;
};