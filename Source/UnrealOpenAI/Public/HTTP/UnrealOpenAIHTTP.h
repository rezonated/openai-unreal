// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "UObject/Object.h"
#include "UnrealOpenAIHTTP.generated.h"

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int index;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs;

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
struct FCreateCompletionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt = "<|endoftext|>";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString suffix;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int max_tokens = 128;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float temperature = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float top_p = 1.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int n = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool stream = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs = 5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool echo = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString stop;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float presence_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float frequency_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int best_of = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, FString> logit_bias;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString user;
};

UENUM(BlueprintType)
enum class ECompletionModel : uint8
{
	ECM_Davinci UMETA(DisplayName = "Davinci"),
	ECM_Curie UMETA(DisplayName = "Curie"),
	ECM_Babbage UMETA(DisplayName = "Babbage"),
	ECM_Ada UMETA(DisplayName = "Ada"),

	ECM_MAX UMETA(Hidden)
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FCompletionRequestCallbackSignature, FString, Id, FString, Object, FString, Created, FString, Model, FChoice, Choices, FUsage, Usage);

UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPCompletionRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCompletionRequestCallbackSignature OnCompletionRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FCompletionRequestCallbackSignature OnCompletionRequestFailed;

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Completion")
	static UUnrealOpenAIHTTPCompletionRequest* CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel);

	TArray<FString> CompletionModels =
	{
		"text-davinci-003",
		"text-curie-001",
		"text-babbage-001",
		"text-ada-001"
	};

	UObject* WorldContextObject;
	FString Prompt;
	ECompletionModel CompletionModel;

	FString Id;
	FString Object;
	FString Created;
	FString Model;
	FChoice Choices;
	FUsage Usage;
};
