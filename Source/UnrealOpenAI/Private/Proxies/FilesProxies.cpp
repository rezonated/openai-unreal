// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/FilesProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/UnrealOpenAIUtils.h"
#include "Utils/Utils.h"

UListFilesRequestProxy* UListFilesRequestProxy::ListFilesRequest(UObject* WorldContextObject)
{
	UListFilesRequestProxy* Proxy = NewObject<UListFilesRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}

void UListFilesRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FListFilesResponse(), TEXT(""));
		return;
	}

	SendPayload(TEXT("files"), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FListFilesResponse ListFilesResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFilesResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFilesResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FListFilesResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFilesResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFilesResponse(), TEXT(""));
	});
}

UUploadFileRequestProxy* UUploadFileRequestProxy::UploadFileRequest(UObject* WorldContextObject, FFileToLoad FileToLoad,
	FString Purpose)
{
	UUploadFileRequestProxy* Proxy = NewObject<UUploadFileRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FileToLoad = FileToLoad;
	Proxy->Purpose = Purpose;
	return Proxy;
}

void UUploadFileRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");

		OnFailure.Broadcast(FFileResponse(), TEXT(""));
		return;
	}

	if (FileToLoad.FileData.Num() > 1024 * 1024 * 1024)
	{
		PrintDebugLogAndOnScreen("File is too big");
		OnFailure.Broadcast(FFileResponse(), TEXT(""));
		return;
	}

	FCreateFileRequest RequestPayload;
	RequestPayload.purpose = Purpose;
	RequestPayload.file = FileToLoad;

	TArray<uint8> CombinedContent;

	CombinedContent.Append(FStringToUInt8(AddData("purpose", RequestPayload.purpose)));

	const FString FileBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"file\";  " + FString::Printf(TEXT("filename=\"%s\""), *FileToLoad.FileName) + "\r\n\r\n";

	CombinedContent.Append(FStringToUInt8(FileBoundary));
	CombinedContent.Append(FileToLoad.FileData);
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("files", CombinedContent, EHTTPMethod::EHP_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FFileResponse UploadFileResponse;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &UploadFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(UploadFileResponse, Response->GetContentAsString());
			}else
			{
				PrintDebugLogAndOnScreen("Failed to parse response to JSON struct.");
				OnFailure.Broadcast(FFileResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete image variation request");
			OnFailure.Broadcast(FFileResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to process image variation request");
		OnFailure.Broadcast(FFileResponse(), TEXT(""));
	});
}

UDeleteFileRequestProxy* UDeleteFileRequestProxy::DeleteFileRequest(UObject* WorldContextObject, FString FileID)
{
	UDeleteFileRequestProxy* Proxy = NewObject<UDeleteFileRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FileID = FileID;
	return Proxy;
}

void UDeleteFileRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("files/%s"), *FileID), TEXT(""), EHTTPMethod::EHP_DELETE, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FDeleteResponse DeleteFileResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &DeleteFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(DeleteFileResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
	});
}

URetrieveFileRequestProxy* URetrieveFileRequestProxy::RetrieveFileRequest(UObject* WorldContextObject, FString FileID)
{
	URetrieveFileRequestProxy* Proxy = NewObject<URetrieveFileRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FileID = FileID;
	return Proxy;
}

void URetrieveFileRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FFileResponse(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("files/%s"), *FileID), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FFileResponse RetrieveFileResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &RetrieveFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(RetrieveFileResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FFileResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FFileResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FFileResponse(), TEXT(""));
	});
}

URetrieveFileContentRequestProxy* URetrieveFileContentRequestProxy::RetrieveFileContentRequest(
	UObject* WorldContextObject, FString FileID)
{
	URetrieveFileContentRequestProxy* Proxy = NewObject<URetrieveFileContentRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FileID = FileID;
	return Proxy;
}

void URetrieveFileContentRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FFileToLoad());
		return;
	}

	const auto DownloadFileFromURL = UUnrealOpenAIUtilsDownloadFileFromURL::DownloadFileFromURL(WorldContextObject, FString::Printf(TEXT("%sfiles/%s"), *BaseURL, *FileID));

	DownloadFileFromURL->OnSuccess.AddDynamic(this, &URetrieveFileContentRequestProxy::OnDownloadFileFromURLSuccess);
	DownloadFileFromURL->OnFailure.AddDynamic(this, &URetrieveFileContentRequestProxy::OnDownloadFileFromURLFailure);

	DownloadFileFromURL->Activate();
}

void URetrieveFileContentRequestProxy::OnDownloadFileFromURLSuccess(FFileToLoad FileData)
{
	OnSuccess.Broadcast(FileData);
}

void URetrieveFileContentRequestProxy::OnDownloadFileFromURLFailure(FFileToLoad FileData)
{
	OnFailure.Broadcast(FFileToLoad());
}
