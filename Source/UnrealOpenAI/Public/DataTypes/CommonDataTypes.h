﻿// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.generated.h"


// Logprobs, used for completions requests:
// https://beta.openai.com/docs/api-reference/completions/create#completions/create-logprobs
USTRUCT(BlueprintType)
struct FLogprobs
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Logprobs")
	TArray<FString> tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Logprobs")
	TArray<float> token_logprobs;
	
	TArray<TMap<FString, float>> top_logprobs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Logprobs")
	TArray<int> text_offset;
};

// Choice, used for completions, and edits requests
USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	FString text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	int index {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	FLogprobs logprobs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Choice")
	FString finish_reason;
};

// Usage, used for completions, edits, and embeddings requests
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

// File struct, used for files and image requests
USTRUCT(BlueprintType)
struct FOpenAIFile
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	int32 bytes {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	int32 created_at {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString filename;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString purpose;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File")
	FString status_details;
};

// Custom helper struct to wrap the file data, name, and extension for uploading files
// using multipart/form-data
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

// Delete response, used for delete requests such as files, and fine-tunes
USTRUCT(BlueprintType)
struct FDeleteResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	FString id;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Delete Response")
	bool deleted {false};
};

// Error data used for handling errors from API 
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