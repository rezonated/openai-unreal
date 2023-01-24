// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "EmbeddingsDataTypes.generated.h"

// Struct to hold the data for a single embedding
USTRUCT(BlueprintType)
struct FEmbeddingData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	TArray<float> embedding;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Embedding Data")
	int index {0};
};

// Struct to construct a request to create embeddings as JSON, described in:
// https://beta.openai.com/docs/api-reference/embeddings/create
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

// Struct to construct a response to create embeddings as JSON, described in:
// https://beta.openai.com/docs/api-reference/embeddings/create
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

