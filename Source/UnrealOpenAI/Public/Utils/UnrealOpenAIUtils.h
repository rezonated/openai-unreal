// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CommonDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "UnrealOpenAIUtils.generated.h"

// Class for BP utility functions used in the plugin. Can be called from C++ as well
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtils : public UObject
{
	GENERATED_BODY()
public:
	/**
	 * Opens a file dialog to load an image, defaults to PNG 
	 * @param DialogTitle Load image dialog title
	 * @param SizeLimitInMB Size limit in MegaBytes
	 * @param OutFileData File data result if successful
	 * @return true if the file was loaded successfully
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenLoadImageDialog(FString DialogTitle, int32 SizeLimitInMB, FFileToLoad& OutFileData);

	/**
	 * Opens a file dialog to load a file
	 * @param DialogTitle Load file dialog title
	 * @param FileExtension File extension to filter
	 * @param SizeLimitInMB Size limit in MegaBytes
	 * @param OutFileData File data result if successful
	 * @return true if the file was loaded successfully
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenLoadFileDialog(FString DialogTitle, FString FileExtension, int32 SizeLimitInMB, FFileToLoad& OutFileData);

	/**
	 * Opens a file dialog to save a file
	 * @param DialogTitle Save file dialog title
	 * @param FileData File data to save
	 * @param FileName Saved file filename
	 * @param FileExtension Saved file extension
	 * @param OutFilePath Saved file path
	 * @return true if the file was saved successfully
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool OpenSaveFileDialog(FString DialogTitle, TArray<uint8> FileData, FString FileName, FString FileExtension, FString& OutFilePath);

	/**
	 * Converts bytes of a file to a Texture2D
	 * @param FileData File data to convert in bytes
	 * @param OutTexture Texture2D result if successful
	 * @return true if the conversion was successful
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBytesToTexture2D(TArray<uint8>FileData, UTexture2D*& OutTexture);

	/**
	 * Converts base64 encoded data string to a Texture2D
	 * @param Base64Data Base64 encoded data string to convert
	 * @param OutTexture Texture2D result if successful
	 * @return true if the conversion was successful
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBase64ToTexture2D(FString Base64Data, UTexture2D*& OutTexture);

	/**
	 * Converts bytes of a file to a base64 encoded data string
	 * @param Base64Data Base64 encoded data string to convert
	 * @param OutBytes Bytes result if successful
	 * @return true if the conversion was successful
	 */
	UFUNCTION(BlueprintCallable, Category = "UnrealOpenAIUtils", meta=(ExpandBoolAsExecs="ReturnValue"))
	static bool ConvertBase64ToBytes(FString Base64Data, TArray<uint8>& OutBytes);
};

// Delegate for the GetImageFromURL function. It will return a Texture2D if successful
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetImageFromURLRequestCallbackSignature, UTexture2D*, Texture2D);

// Class for utility to get an image from a URL 
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtilsGetImageFromURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Delegate to call when the request is successful, will return a Texture2D from URL
	 */
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnSuccess;

	/**
	 * Delegate to call when the request fails, will return a null Texture2D
	 */
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnFailure;

	/**
	 * Gets an image from a URL
	 * @param WorldContextObject Function caller for getting the world context 
	 * @param URL URL to get the image from
	 * @return Proxy object for the function
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAIUtils | GetImageFromURL")
	static UUnrealOpenAIUtilsGetImageFromURL* GetImageFromURL(UObject* WorldContextObject, FString URL);

	/**
	 * Activates the function, called by the proxy object. If using C++ call this function
	 * directly to execute the function
	 */
	virtual void Activate() override;

private:
	/**
	 * Callback for when the get image from URL request is complete
	 * @param HttpRequest HTTP request object
	 * @param HttpResponse HTTP response object
	 * @param bSuccessful true if the request was successful
	 */
	void OnProcessRequestComplete(TSharedPtr<class IHttpRequest, ESPMode::ThreadSafe> HttpRequest, TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful);

	/**
	 * World context object for the function
	 */
	UObject* WorldContextObject;

	/**
	 * Current URL to get the image from
	 */
	FString URL;

	/**
	 * Texture2D result from the request
	 */
	UPROPERTY(Transient)
	UTexture2D* Texture2D;
};

// Delegate for the DownloadFileFromURL function. It will return a FFileToLoad if
// successful
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDownloadFileFromURLRequestCallbackSignature, FFileToLoad, FileData);

// Class for utility to download a file from a URL
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtilsDownloadFileFromURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Delegate to call when the request is successful, will return a FFileToLoad from URL
	 */
	UPROPERTY(BlueprintAssignable)
	FDownloadFileFromURLRequestCallbackSignature OnSuccess;

	/**
	 * Delegate to call when the request fails, will return an empty FFileToLoad
	 */
	UPROPERTY(BlueprintAssignable)
	FDownloadFileFromURLRequestCallbackSignature OnFailure;

	/**
	 * Downloads a file from a URL
	 * @param WorldContextObject Function caller for getting the world context
	 * @param URL URL to download the file from
	 * @return Proxy object for the function
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAIUtils | DownloadFileFromURL")
	static UUnrealOpenAIUtilsDownloadFileFromURL* DownloadFileFromURL(UObject* WorldContextObject, FString URL);

	/**
	 * Callback for when the download file from URL request is complete
	 * @param HttpRequest HTTP request object
	 * @param HttpResponse HTTP response object
	 * @param bSuccessful true if the request was successful
	 */
	void OnProcessRequestComplete(TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest, TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful);

	/**
	 * Activates the function, called by the proxy object. If using C++ call this function
	 * to execute the function
	 */
	virtual void Activate() override;

private:
	/**
	 * World context object for the function
	 */
	UObject* WorldContextObject;

	/**
	 * Current URL to download the file from
	 */
	FString URL;

	/**
	 * File data result from the request
	 */
	FFileToLoad FileData;
};