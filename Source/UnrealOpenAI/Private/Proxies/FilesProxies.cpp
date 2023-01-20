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
		OnFailure.Broadcast(FListFilesResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	SendPayload(TEXT("files"), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
			
			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FListFilesResponse(), ResponseString, ErrorMessage);
				return;
			}
				
			FListFilesResponse ListFilesResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFilesResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFilesResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FListFilesResponse(), TEXT(""), TEXT("Failed to convert list files response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FListFilesResponse(), TEXT(""), TEXT("List files request failed"));
		}
	}, [this]
	{
			OnFailure.Broadcast(FListFilesResponse(), TEXT(""), TEXT("Failed to send list files request"));
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
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FileToLoad.FileData.Num() > 1024 * 1024 * 1024)
	{
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("File size is too big"));
		return;
	}

	if (Purpose.IsEmpty() || Purpose == TEXT("") || Purpose.Len() <= 0)
	{
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Purpose is empty"));
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
		if(!bWasSuccessful)
		{
			OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Upload file request failed"));
		}
		else
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FFileResponse(), ResponseString, ErrorMessage);
				return;
			}

			FFileResponse UploadFileResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &UploadFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(UploadFileResponse, Response->GetContentAsString(), TEXT(""));
			}else
			{
				OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Failed to parse upload file response to struct."));
			}
		}
	}, [this]
	{
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Failed to send upload file request"));
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
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FileID.IsEmpty() || FileID == TEXT("") || FileID.Len() <= 0)
	{
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("FileID is empty"));
		return;
	}

	SendPayload(FString::Printf(TEXT("files/%s"), *FileID), TEXT(""), EHTTPMethod::EHP_DELETE, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FDeleteResponse(), ResponseString, ErrorMessage);
				return;
			}
			
			FDeleteResponse DeleteFileResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &DeleteFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(DeleteFileResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Failed to convert delete file response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Delete file request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Failed to send delete file request"));
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
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if(FileID.IsEmpty() || FileID == TEXT("") || FileID.Len() <= 0)
	{
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("FileID is empty"));
		return;
	}

	SendPayload(FString::Printf(TEXT("files/%s"), *FileID), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FFileResponse(), ResponseString, ErrorMessage);
				return;
			}
			
			FFileResponse RetrieveFileResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &RetrieveFileResponse, 0, 0))
			{
				OnSuccess.Broadcast(RetrieveFileResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Failed to convert retrieve file response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Retrieve file request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FFileResponse(), TEXT(""), TEXT("Failed to send delete file request"));
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
		OnFailure.Broadcast(FFileToLoad(), TEXT("WorldContextObject is null"));
		return;
	}

	if (FileID.IsEmpty() || FileID == TEXT("") || FileID.Len() <= 0)
	{
		OnFailure.Broadcast(FFileToLoad(), TEXT("FileID is empty"));
		return;
	}

	const auto DownloadFileFromURL = UUnrealOpenAIUtilsDownloadFileFromURL::DownloadFileFromURL(WorldContextObject, FString::Printf(TEXT("%sfiles/%s"), *BaseURL, *FileID));

	DownloadFileFromURL->OnSuccess.AddDynamic(this, &URetrieveFileContentRequestProxy::OnDownloadFileFromURLSuccess);
	DownloadFileFromURL->OnFailure.AddDynamic(this, &URetrieveFileContentRequestProxy::OnDownloadFileFromURLFailure);

	DownloadFileFromURL->Activate();
}

void URetrieveFileContentRequestProxy::OnDownloadFileFromURLSuccess(FFileToLoad FileData)
{
	OnSuccess.Broadcast(FileData, TEXT(""));
}

void URetrieveFileContentRequestProxy::OnDownloadFileFromURLFailure(FFileToLoad FileData)
{
	OnFailure.Broadcast(FFileToLoad(), TEXT("Failed to download file from URL"));
}
