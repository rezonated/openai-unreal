// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/EmbeddingsProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Embedding Proxies

UCreateEmbeddingsRequestProxy* UCreateEmbeddingsRequestProxy::CreateEmbeddings(UObject* WorldContextObject, FString Input)
{
	UCreateEmbeddingsRequestProxy* Proxy = NewObject<UCreateEmbeddingsRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	return Proxy;
}

void UCreateEmbeddingsRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Input.IsEmpty() || Input == TEXT("") || Input.Len() <= 0)
	{
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Input is empty"));
		return;
	}
	FString JSONPayload;

	FCreateEmbeddingsRequest RequestPayload;
	RequestPayload.input = Input;

	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("embeddings"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FCreateEmbeddingsResponse(), ResponseString, ErrorMessage);
				return;
			}
				
			FCreateEmbeddingsResponse EmbeddingsResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EmbeddingsResponse, 0, 0))
			{
				OnSuccess.Broadcast(EmbeddingsResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Failed to convert create embeddings response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Create embeddings request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Failed to send create embeddings request"));
	});
}

#pragma endregion