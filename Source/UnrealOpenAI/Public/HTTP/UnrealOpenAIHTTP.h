// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/DataTypes.h"
#include "Enums/Enums.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "UnrealOpenAIHTTP.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateCompletionRequestCallbackSignature, FCreateCompletionResponse, Response, FString, JSONString);

UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPCompletionRequest : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	virtual void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnCompletionRequestComplete;
	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnCompletionRequestFailed;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Completion")
	static UUnrealOpenAIHTTPCompletionRequest* CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel);

private:
	
	UObject* WorldContextObject;
	FString Prompt;
	ECompletionModel CompletionModel;
	
	FCreateCompletionResponse Response;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FImageVariationRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageVariationRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FImageVariationRequestCallbackSignatureURL OnImageVariationRequestCompleteURL;
	UPROPERTY(BlueprintAssignable)
	FImageVariationRequestCallbackSignatureURL OnImageVariationRequestFailedURL;
	

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageVariationRequestURL* CreateImageVariationURL(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	EImageSize ImageSize;

	FCreateImageResponseURL ResponseURL;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FImageVariationRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageVariationRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FImageVariationRequestCallbackSignatureBase64JSON OnImageVariationRequestCompleteBase64JSON;
	UPROPERTY(BlueprintAssignable)
	FImageVariationRequestCallbackSignatureBase64JSON OnImageVariationRequestFailedBase64JSON;

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageVariationRequestBase64JSON* CreateImageVariationJSON(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	EImageSize ImageSize;
	
	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FImageEditRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageEditRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FImageEditRequestCallbackSignatureURL OnImageEditRequestCompleteURL;
	UPROPERTY(BlueprintAssignable)
	FImageEditRequestCallbackSignatureURL OnImageEditRequestFailedURL;
	

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageEditRequestURL* CreateImageEditURL(UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	TArray<uint8> Mask;
	FString Prompt;
	EImageSize ImageSize;

	FCreateImageResponseURL ResponseURL;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FImageEditRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageEditRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FImageEditRequestCallbackSignatureBase64JSON OnImageEditRequestCompleteBase64JSON;
	UPROPERTY(BlueprintAssignable)
	FImageEditRequestCallbackSignatureBase64JSON OnImageEditRequestFailedBase64JSON;

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageEditRequestBase64JSON* CreateImageEditJSON(UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	TArray<uint8> Mask;
	FString Prompt;
	EImageSize ImageSize;
	
	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
};