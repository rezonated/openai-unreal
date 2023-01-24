// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/EmbeddingsProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Embedding Proxies

UCreateEmbeddingsRequestProxy* UCreateEmbeddingsRequestProxy::CreateEmbeddings(UObject* WorldContextObject, FString Input)
{
	// Create a new proxy object and set the parameters, then return it
	UCreateEmbeddingsRequestProxy* Proxy = NewObject<UCreateEmbeddingsRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	return Proxy;
}

void UCreateEmbeddingsRequestProxy::Activate()
{
	Super::Activate();

	// Check if the WorldContextObject is valid
	if (!WorldContextObject)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	// Check if the Input is valid
	if (Input.IsEmpty() || Input == TEXT("") || Input.Len() <= 0)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Input is empty"));
		return;
	}

	// Create the struct payload and FString to store the converted JSON
	FString JSONPayload;
	FCreateEmbeddingsRequest RequestPayload;
	RequestPayload.input = Input;

	// Convert the struct to JSON 
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	// Send the request containing the JSON payload using POST method to the URL passing
	// the callback functions to handle the response
	SendPayload(TEXT("embeddings"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		// Check if the response was successful
		if (bWasSuccessful)
		{
			// Get the response as a string and sanitize it
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			// Check if the response contains an error message
			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				// If it does, broadcast the failure event with the error message
				OnFailure.Broadcast(FCreateEmbeddingsResponse(), ResponseString, ErrorMessage);
				return;
			}

			// Convert the JSON response to a struct and check if it was successful
			FCreateEmbeddingsResponse EmbeddingsResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EmbeddingsResponse, 0, 0))
			{
				// If it was, broadcast the success event with the response struct
				OnSuccess.Broadcast(EmbeddingsResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				// If it wasn't, broadcast the failure event with the error message
				OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Failed to convert create embeddings response to struct"));
			}
		}
		else
		{
			// If the response wasn't successful, broadcast the failure event with the
			// error message
			OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Create embeddings request failed"));
		}
	}, [this]
	{
		// If the request failed, broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEmbeddingsResponse(), TEXT(""), TEXT("Failed to send create embeddings request"));
	});
}

#pragma endregion