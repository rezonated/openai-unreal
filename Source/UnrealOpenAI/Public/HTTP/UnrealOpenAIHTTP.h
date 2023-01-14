// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/DataTypes.h"
#include "Enums/Enums.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "UnrealOpenAIHTTP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCompletionRequestCallbackSignature, FCreateCompletionResponse, Response, FString, JSONString);

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
	
	FCreateCompletionResponse Response;
	FString JSONString;
};
