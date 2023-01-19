// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString text;
	
	TOptional<int> index;
	
	TOptional<int> logprobs;

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
struct FOpenAIFile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 bytes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created_at;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString filename;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString purpose;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString status_details;
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

USTRUCT(BlueprintType)
struct FDeleteResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool deleted;
};