// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/CompletionProxies.h"

#include "JsonObjectConverter.h"
#include "Constants/CompletionConstants.h"
#include "Enums/CompletionEnums.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Completion Proxy

UCreateCompletionRequestProxy* UCreateCompletionRequestProxy::CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel)
{
	// Create a new proxy object and set the parameters, then return it
	UCreateCompletionRequestProxy* CompletionRequest = NewObject<UCreateCompletionRequestProxy>();
	CompletionRequest->WorldContextObject = WorldContextObject;
	CompletionRequest->Prompt = Prompt;
	CompletionRequest->CompletionModel = CompletionModel;
	return CompletionRequest;
}

void UCreateCompletionRequestProxy::Activate()
{
	Super::Activate();

	// Check if the WorldContextObject is valid
	if (!WorldContextObject)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	// Check if the Prompt is valid
	if (Prompt.IsEmpty() || Prompt == TEXT("") || Prompt.Len() <= 0)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}

	// Check if the CompletionModel is valid
	if (CompletionModel == ECompletionModel::ECM_MAX)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("CompletionModel is invalid"));
		return;	
	}

	// Create the struct payload and FString to store the converted JSON 
	FString JSONPayload;
	FCreateCompletionRequest RequestPayload;
	RequestPayload.model = CompletionModels[static_cast<int>(CompletionModel)];
	RequestPayload.prompt = Prompt;

	// Convert the struct to JSON
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	// Send the request containing the JSON payload using POST method to the URL passing
	// the callback functions to handle the response
	SendPayload(
		TEXT("completions"),
		JSONPayload, EHTTPMethod::EHP_POST,
			[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
				// Check if the request was successful
			if (bWasSuccessful)
			{
				// Get the response as a string and sanitize it
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				// Check if the response contains an error
				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					// If it does, broadcast the error message
					OnFailure.Broadcast(FCreateCompletionResponse(), ResponseString, ErrorMessage);
					return;
				}

				// Convert the response to a struct and check if it was successful
				FCreateCompletionResponse CreateCompletionResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateCompletionResponse, 0, 0))
				{
					// If it was, broadcast the response
					OnSuccess.Broadcast(CreateCompletionResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					// If it wasn't, broadcast the error message
					OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Failed to convert create completion response to struct"));
				}
			}
			else
			{
				// If the request wasn't successful, broadcast the error message
				OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Create completion request failed"));
			}
	},
	[this]
	{
			// If the request failed to send, broadcast the error message
			OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Failed to send create completion request"));
		}
	);
}

#pragma endregion