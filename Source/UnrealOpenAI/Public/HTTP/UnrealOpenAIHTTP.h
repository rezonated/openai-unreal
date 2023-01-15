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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageRequestCallbackSignatureURL, FCreateImageResponseURL, Response, FString, JSONString);

UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnImageRequestCompleteURL;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnImageRequestFailedURL;

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageRequestURL* CreateImageURL(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;

	FCreateImageResponseURL ResponseURL;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, Response, FString, JSONString);

UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnImageRequestCompleteBase64JSON;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnImageRequestFailedBase64JSON;

public:

	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UUnrealOpenAIHTTPImageRequestBase64JSON* CreateImageBase64JSON(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;

	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageVariationRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageVariationRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnImageVariationRequestCompleteURL;
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnImageVariationRequestFailedURL;
	

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageVariationRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageVariationRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnImageVariationRequestCompleteBase64JSON;
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnImageVariationRequestFailedBase64JSON;

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageEditRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageEditRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnImageEditRequestCompleteURL;
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnImageEditRequestFailedURL;
	

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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageEditRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIHTTPImageEditRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnImageEditRequestCompleteBase64JSON;
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnImageEditRequestFailedBase64JSON;

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