// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/ModerationProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Moderation Proxies

UCreateModerationRequestProxy* UCreateModerationRequestProxy::CreateModerationRequest(UObject* WorldContextObject, FString Input, EModerationModels Model)
{
	// Create a new proxy object and set the parameters, then return it
	UCreateModerationRequestProxy* Proxy = NewObject<UCreateModerationRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	Proxy->Model = Model;
	return Proxy;
}

void UCreateModerationRequestProxy::Activate()
{
	Super::Activate();

	// Check if the WorldContextObject is valid
	if (!WorldContextObject)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	// Check if the Input is valid
	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Input is empty"));
	}

	// Create the struct payload and FString to store the converted JSON
	FString JSONPayload;
	FCreateModerationRequest RequestPayload;
	RequestPayload.input = Input;
	RequestPayload.model = ModerationModels[static_cast<int>(Model)];

	// Convert the struct to JSON
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	// Send the request containing the JSON payload using POST method to the URL passing
	// the callback functions to handle the response 
	SendPayload(
		TEXT("moderations"),
		JSONPayload, EHTTPMethod::EHP_POST,
			[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
				// Check if the request was successful
			if (bWasSuccessful)
			{
				// Get the response as a string and sanitize it
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				// Check if the response contains an error message
				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					// If it does, broadcast the failure event with the error message
					OnFailure.Broadcast(FCreateModerationResponse(), ResponseString, ErrorMessage);
					return;
				}

				// Convert the response to a struct and check if it was successful
				FCreateModerationResponse ModerationResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ModerationResponse, 0, 0))
				{
					// If it was, broadcast the success event with the response
					OnSuccess.Broadcast(ModerationResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					// If it wasn't, broadcast the failure event with the error message
					OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Failed to convert create moderation response to struct"));
				}
			}
			else
			{
				// If the request wasn't successful, broadcast the failure event with the
				// error message
				OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Create moderation request failed"));
			}
	},
	[this]
	{
			// If the request failed to send, broadcast the failure event with the error
			// message
			OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Failed to send create moderation request"));
		}
	);
}

#pragma endregion