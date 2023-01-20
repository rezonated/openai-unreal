// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/FilesDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FilesProxies.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFilesRequestCallbackSignature, FListFilesResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UListFilesRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FListFilesRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListFilesRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
		static UListFilesRequestProxy* ListFilesRequest(UObject* WorldContextObject);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateFileRequestCallbackSignature, FFileResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UUploadFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateFileRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateFileRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
		static UUploadFileRequestProxy* UploadFileRequest(UObject* WorldContextObject, FFileToLoad FileToLoad, FString Purpose);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FFileToLoad FileToLoad;
	FString Purpose;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleteFileRequestCallbackSignature, FDeleteResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UDeleteFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FDeleteFileRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteFileRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
		static UDeleteFileRequestProxy* DeleteFileRequest(UObject* WorldContextObject, FString FileID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FileID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRetrieveFileRequestCallbackSignature, FFileResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API URetrieveFileRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FRetrieveFileRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRetrieveFileRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
		static URetrieveFileRequestProxy* RetrieveFileRequest(UObject* WorldContextObject, FString FileID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FileID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateFileRequestCallbackSignature, FFileToLoad, Response, FString, Error);
UCLASS()
class UNREALOPENAI_API URetrieveFileContentRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FUpdateFileRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateFileRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Files")
		static URetrieveFileContentRequestProxy* RetrieveFileContentRequest(UObject* WorldContextObject, FString FileID);
	
	virtual void Activate() override;

	UFUNCTION()
	void OnDownloadFileFromURLSuccess(FFileToLoad FileData);

	UFUNCTION()
	void OnDownloadFileFromURLFailure(FFileToLoad FileData);

private:
	UObject* WorldContextObject;
	FString FileID;
};
