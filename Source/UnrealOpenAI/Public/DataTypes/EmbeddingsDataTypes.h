// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "EmbeddingsDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FEmbeddingData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	TArray<float> embedding;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	int index;
};


USTRUCT(BlueprintType)
struct FCreateEmbeddingsRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Request")
	FString model = "text-embedding-ada-002";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Request")
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Request")
	FString user;
};


USTRUCT(BlueprintType)
struct FCreateEmbeddingsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Response")
	TArray<FEmbeddingData> data;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Response")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Embeddings Response")
	FUsage usage;
	
};

