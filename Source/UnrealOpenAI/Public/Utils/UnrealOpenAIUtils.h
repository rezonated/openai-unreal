// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CommonDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "UnrealOpenAIUtils.generated.h"
/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtils : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenLoadImageDialog(FString DialogTitle, int32 SizeLimitInMB, FFileToLoad& OutFileData);

	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenLoadFileDialog(FString DialogTitle, FString FileExtension, int32 SizeLimitInMB, FFileToLoad& OutFileData);

	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenSaveFileDialog(FString DialogTitle, TArray<uint8> FileData, FString FileName, FString FileExtension, FString& OutFilePath);
	
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBytesToTexture2D(TArray<uint8>FileData, UTexture2D*& OutTexture);

	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBase64ToTexture2D(FString Base64Data, UTexture2D*& OutTexture);

	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBase64ToBytes(FString Base64Data, TArray<uint8>& OutBytes);
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetImageFromURLRequestCallbackSignature, UTexture2D*, Texture2D);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtilsGetImageFromURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAIUtils | GetImageFromURL")
	static UUnrealOpenAIUtilsGetImageFromURL* GetImageFromURL(UObject* WorldContextObject, FString URL);

	virtual void Activate() override;

private:
	void OnProcessRequestComplete(TSharedPtr<class IHttpRequest, ESPMode::ThreadSafe> HttpRequest, TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful);
	
	UObject* WorldContextObject;
	FString URL;

	UPROPERTY(Transient)
	UTexture2D* Texture2D;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadFileFromURLRequestCallbackSignature, FFileToLoad, FileData);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtilsDownloadFileFromURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDownloadFileFromURLRequestCallbackSignature OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FDownloadFileFromURLRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAIUtils | DownloadFileFromURL")
	static UUnrealOpenAIUtilsDownloadFileFromURL* DownloadFileFromURL(UObject* WorldContextObject, FString URL);

	void OnProcessRequestComplete(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful);
	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString URL;

	FFileToLoad FileData;
};