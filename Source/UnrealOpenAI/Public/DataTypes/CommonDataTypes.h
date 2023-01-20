// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	FString text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	int index;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	int logprobs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	FString finish_reason;
};

USTRUCT(BlueprintType)
struct FUsage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Usage")
	FString prompt_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Usage")
	FString completion_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Usage")
	FString total_tokens;
};

USTRUCT(BlueprintType)
struct FOpenAIFile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	int32 bytes;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	int32 created_at;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString filename;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString purpose;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString status_details;
};

USTRUCT(BlueprintType)
struct FFileToLoad
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File To Load")
	TArray<uint8> FileData;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File To Load")
	FString FileName;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File To Load")
	FString FileExtension;
};

USTRUCT(BlueprintType)
struct FDeleteResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	FString id;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	bool deleted;
};

USTRUCT(BlueprintType)
struct FErrorData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Error Data")
	FString message;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Error Data")
	FString type;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Error Data")
	FString param;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Error Data")
	FString code;
};

USTRUCT(BlueprintType)
struct FErrorResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Error Response")
	FErrorData error;
};