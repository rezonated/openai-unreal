// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CompletionDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "CompletionProxies.generated.h"

#pragma region Create Completion Proxy

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateCompletionRequestCallbackSignature, FCreateCompletionResponse, Response, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateCompletionProxies : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnCompletionRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnCompletionRequestFailed;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Completion")
	static UCreateCompletionProxies* CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel);

	virtual void Activate() override;

private:
	
	UObject* WorldContextObject;
	FString Prompt;
	ECompletionModel CompletionModel;
	
	FCreateCompletionResponse Response;
	FString JSONString;
	
};

#pragma endregion