// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "FilesDataTypes.generated.h"

// Struct to construct response for list files response, as described in:
// https://beta.openai.com/docs/api-reference/files/list
USTRUCT(BlueprintType)
struct FListFilesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | List Files Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | List Files Response")
	TArray<FOpenAIFile> data;
};

// Struct to construct request for create file response as JSON, described in:
// https://beta.openai.com/docs/api-reference/files/create
USTRUCT(BlueprintType)
struct FCreateFileRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create File Request")
	FFileToLoad file;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create File Request")
	FString purpose;
};

// Struct to construct response for file operations responses as JSON, described in:
// https://beta.openai.com/docs/api-reference/files
USTRUCT(BlueprintType)
struct FFileResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	int32 bytes {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	int32 created_at {0};
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	FString filename;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | File Response")
	FString purpose;
};