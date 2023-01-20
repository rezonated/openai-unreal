// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "FilesDataTypes.generated.h"


USTRUCT(BlueprintType)
struct FListFilesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | List Files Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | List Files Response")
	TArray<FOpenAIFile> data;
};


USTRUCT(BlueprintType)
struct FCreateFileRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create File Request")
	FFileToLoad file;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create File Request")
	FString purpose;
};

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