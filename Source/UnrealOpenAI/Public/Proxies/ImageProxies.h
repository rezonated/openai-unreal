// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/ImageDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ImageProxies.generated.h"

#pragma region Create Image Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageRequestCallbackSignatureURL, FCreateImageResponseURL, Response, FString, JSONString);

UCLASS()
class UNREALOPENAI_API UCreateImageRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageRequestURL* CreateImageURL(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;

	FCreateImageResponseURL ResponseURL;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, Response, FString, JSONString);

UCLASS()
class UNREALOPENAI_API UCreateImageRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageRequestBase64JSON* CreateImageBase64JSON(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;

	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
	
};

#pragma endregion

#pragma region Create Image Edit Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageEditRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateImageEditRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnFailure;
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageEditRequestURL* CreateImageEditURL(UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize);

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
class UNREALOPENAI_API UCreateImageEditRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnFailure;
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageEditRequestBase64JSON* CreateImageEditJSON(UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	TArray<uint8> Mask;
	FString Prompt;
	EImageSize ImageSize;
	
	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
};

#pragma endregion

#pragma region Create Image Variation Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageVariationRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateImageVariationRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnFailure;
	

public:
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageVariationRequestURL* CreateImageVariationURL(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	EImageSize ImageSize;

	FCreateImageResponseURL ResponseURL;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateImageVariationRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateImageVariationRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnFailure;
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI - Images")
	static UCreateImageVariationRequestBase64JSON* CreateImageVariationJSON(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	TArray<uint8> Image;
	EImageSize ImageSize;
	
	FCreateImageResponseBase64JSON ResponseBase64JSON;
	FString JSONString;
};


#pragma endregion 