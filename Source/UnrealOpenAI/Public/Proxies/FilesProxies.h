// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/FilesDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FilesProxies.generated.h"


#pragma region List Files Proxy

// Delegate for the list files request proxy, will return the response in
// FListFilesResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFilesRequestCallbackSignature, FListFilesResponse, Response, FString, JSONString, FString, Error);

// Class to handle the list files request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UListFilesRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the list file request is successful, will return the response in
	 * FListFilesResponse struct, a JSON string response containing either a valid
	 * response or error response, and an error string when the request fails
	 */
	UPROPERTY(BlueprintAssignable)
	FListFilesRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the list file request fails, will return an empty FListFilesResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FListFilesRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the list files request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/files/list
	 *
	 * Returns a list of files that belong to the user's organization.
	 * @param WorldContextObject Function caller to obtain world context
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
	static UListFilesRequestProxy* ListFilesRequest(UObject* WorldContextObject);

	/**
	 * Activates the list files request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;
};
#pragma endregion

#pragma region Create File Proxy

// Delegate for the create file request proxy, will return the response in FFileResponse
// struct, a JSON string response containing either a valid response or error response,
// and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateFileRequestCallbackSignature, FFileResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UUploadFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create file request is successful, will return the response in
	 * FFileResponse struct, a valid JSON string response, and an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateFileRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create file request fails, will return an empty FFileResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateFileRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create file request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/files/upload
	 *
	 * Upload a file that contains document(s) to be used across various
	 * endpoints/features. Currently, the size of all the files uploaded by one
	 * organization can be up to 1 GB. Please contact us if you need to increase the
	 * storage limit.
	 * @param WorldContextObject Function caller to obtain world context 
	 * @param FileToLoad  File to load, can be obtained by calling
	 * UUnrealOpenAIUtils::OpenLoadFileDialog and pick your file
	 * @param Purpose The intended purpose of the uploaded documents.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
	static UUploadFileRequestProxy* UploadFileRequest(UObject* WorldContextObject, FFileToLoad FileToLoad, FString Purpose);

	/**
	 * Activates the create file request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current file to load for the request
	 */
	FFileToLoad FileToLoad;

	/**
	 * Current purpose for the request
	 */
	FString Purpose;
};
#pragma endregion

#pragma region Delete File Proxy

// Delegate for the delete file request proxy, will return the response in FDeleteResponse
// struct, a JSON string response containing either a valid response or error response,
// and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleteFileRequestCallbackSignature, FDeleteResponse, Response, FString, JSONString, FString, Error);

// Class to handle the delete file request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UDeleteFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the delete file request is successful, will return the response in
	 * FDeleteResponse struct, a valid JSON response string and an empty error string 
	 */
	UPROPERTY(BlueprintAssignable)
	FDeleteFileRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the delete file request fails, will return an empty FDeleteResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FDeleteFileRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the delete file request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/files/delete
	 *
	 * Delete a file that belongs to the user's organization, passing the file ID.
	 * @param WorldContextObject  Function caller to obtain world context
	 * @param FileID The ID of the file to use for this request
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
	static UDeleteFileRequestProxy* DeleteFileRequest(UObject* WorldContextObject, FString FileID);

	/**
	 * Activates the delete file request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current file ID for the request
	 */
	FString FileID;
};

#pragma endregion

#pragma region Retrieve File Proxy

// Delegate for the retrieve file request proxy, will return the response in FFileResponse
// struct, a JSON string response containing either a valid response or error response,
// and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRetrieveFileRequestCallbackSignature, FFileResponse, Response, FString, JSONString, FString, Error);

// Class to handle the retrieve file request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API URetrieveFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	/**
	 * Fired when the retrieve file request is successful, will return the response in
	 * FFileResponse struct, a valid JSON response string and an empty error string 
	 */
	UPROPERTY(BlueprintAssignable)
	FRetrieveFileRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the retrieve file request fails, will return an empty FFileResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FRetrieveFileRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the retrieve file request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/files/retrieve
	 *
	 * Returns information about a specific file.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param FileID The ID of the file to use for this request
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
	static URetrieveFileRequestProxy* RetrieveFileRequest(UObject* WorldContextObject, FString FileID);

	/**
	 * Activates the retrieve file request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current file ID for the request
	 */
	FString FileID;
};

#pragma endregion

#pragma region Retrieve File Content Proxy

// Delegate for the retrieve file content request proxy, will return the response in FFileToLoad struct, a JSON string response containing either a valid response or error
// response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateFileRequestCallbackSignature, FFileToLoad, Response, FString, Error);

// Class to handle the retrieve file content request proxy, exposes the OnSuccess and
// OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API URetrieveFileContentRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the retrieve file content request is successful, will return the
	 * response in FFileToLoad struct, a valid JSON response string and an empty error
	 * string
	 */
	UPROPERTY(BlueprintAssignable)
	FUpdateFileRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the retrieve file content request fails, will return an empty
	 * FFileToLoad struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FUpdateFileRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the retrieve file content request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/files/retrieve-content
	 *
	 * Returns the contents of the specified file
	 * @param WorldContextObject Function caller to obtain world context
	 * @param FileID The ID of the file to use for this request
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
	static URetrieveFileContentRequestProxy* RetrieveFileContentRequest(UObject* WorldContextObject, FString FileID);

	/**
	 * Activates the retrieve file content request proxy, call this function in C++ to
	 * execute the request
	 */
	virtual void Activate() override;

	/**
	 * Callback for when the file content is successfully retrieved, will return the file
	 * data loaded from the URL
	 * @param FileData File data to retrieve
	 */
	UFUNCTION()
	void OnDownloadFileFromURLSuccess(FFileToLoad FileData);

	/**
	 * Callback for when the file content fails to be retrieved, will return an empty file
	 * data
	 * @param FileData File data to retrieve
	 */
	UFUNCTION()
	void OnDownloadFileFromURLFailure(FFileToLoad FileData);

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current file ID for the request
	 */
	FString FileID;
};

#pragma endregion