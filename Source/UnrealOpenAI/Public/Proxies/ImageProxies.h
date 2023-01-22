// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CommonDataTypes.h"
#include "DataTypes/ImageDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ImageProxies.generated.h"

#pragma region Create Image Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageRequestCallbackSignatureURL, FCreateImageResponseURL, Response, FString, JSONString, FString, Error);

UCLASS()
class UNREALOPENAI_API UCreateImageRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageRequestURL* CreateImageURL(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, Response, FString, JSONString, FString, Error);

UCLASS()
class UNREALOPENAI_API UCreateImageRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnFailure;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageRequestBase64JSON* CreateImageBase64JSON(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Prompt;
	EImageSize ImageSize;	
};

#pragma endregion

#pragma region Create Image Edit Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageEditRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString, FString, Error);
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

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageEditRequestURL* CreateImageEditURL(UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FFileToLoad ImageFile;
	FFileToLoad MaskImageFile;
	FString Prompt;
	EImageSize ImageSize;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageEditRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString, FString, Error);
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

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageEditRequestBase64JSON* CreateImageEditJSON(UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FFileToLoad ImageFile;
	FFileToLoad MaskImageFile;
	FString Prompt;
	EImageSize ImageSize;
};

#pragma endregion

#pragma region Create Image Variation Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageVariationRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UCreateImageVariationRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
	

public:

	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnFailure;
	
	virtual void Activate() override;

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageVariationRequestURL* CreateImageVariationURL(UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FFileToLoad ImageFile;
	EImageSize ImageSize;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageVariationRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString, FString, Error);
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

	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageVariationRequestBase64JSON* CreateImageVariationJSON(UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize);

private:
	UObject* WorldContextObject;
	FFileToLoad ImageFile;
	EImageSize ImageSize;
};


#pragma endregion 