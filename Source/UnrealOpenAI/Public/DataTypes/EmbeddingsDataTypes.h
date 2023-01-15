// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "EmbeddingsDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FEmbeddingData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<float> embedding;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int index;
};


USTRUCT(BlueprintType)
struct FCreateEmbeddingsRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model = "text-embedding-ada-002";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString user;
};


USTRUCT(BlueprintType)
struct FCreateEmbeddingsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FEmbeddingData> data;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUsage usage;
	
};

