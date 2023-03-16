// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "ChatDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FMessage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Open AI | Chat Completion Message")
	FString role;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Open AI | Chat Completion Message")
	FString content;
};

USTRUCT(BlueprintType)
struct FChatRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Request")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Request")
	TArray<FMessage> messages;
};

USTRUCT(BlueprintType)
struct FChatChoice
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Choice")
	int32 index;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Choice")
	FMessage message;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Choice")
	FString finish_reason;
};

USTRUCT(BlueprintType)
struct FChatUsage
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Usage")
	int32 prompt_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Usage")
	int32 completion_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Usage")
	int32 total_tokens;
};

USTRUCT(BlueprintType)
struct FChatResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	FChatUsage usage;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Chat Completion Response")
	TArray<FChatChoice> choices;
};
