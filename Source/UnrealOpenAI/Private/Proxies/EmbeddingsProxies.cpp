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
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""));
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
				
			FCreateEmbeddingsResponse EmbeddingsResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EmbeddingsResponse, 0, 0))
			{
				OnSuccess.Broadcast(EmbeddingsResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""));
	});
}

#pragma endregion