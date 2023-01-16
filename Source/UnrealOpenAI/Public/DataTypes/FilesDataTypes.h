// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "FilesDataTypes.generated.h"


USTRUCT(BlueprintType)
struct FListFilesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FOpenAIFile> data;
};


USTRUCT(BlueprintType)
struct FFileDeleteResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool deleted;
};


USTRUCT(BlueprintType)
struct FCreateFileRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FFileToLoad file;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString purpose;
};

USTRUCT(BlueprintType)
struct FFileResponse
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
};