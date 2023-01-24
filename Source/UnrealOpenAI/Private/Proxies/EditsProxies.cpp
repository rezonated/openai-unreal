// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/EditsProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Edits Proxies

UCreateEditsRequestProxy* UCreateEditsRequestProxy::CreateEdits(UObject* WorldContextObject, FString Input, FString Instruction)
{
	// Create a new proxy object and set the parameters, then return it
	UCreateEditsRequestProxy* Proxy = NewObject<UCreateEditsRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	Proxy->Instruction = Instruction;
	return Proxy;
}

void UCreateEditsRequestProxy::Activate()
{
	Super::Activate();

	// Check if the WorldContextObject is valid
	if (!WorldContextObject)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	// Check if the Input is valid
	if (Input.IsEmpty() || Input == TEXT("") || Input.Len() <= 0)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Input is empty"));
		return;
	}

	// Check if the Instruction is valid
	if (Instruction.IsEmpty() || Instruction == TEXT("") || Instruction.Len() <= 0)
	{
		// Broadcast the failure event with the error message
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Instruction is empty"));
		return;
	}

	// Create the struct payload and FString to store the converted JSON
	FString JSONPayload;
	FCreateEditsRequest RequestPayload;
	RequestPayload.input = Input;
	RequestPayload.instruction = Instruction;

	// Convert the struct to JSON
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	// Send the request containing the JSON payload using POST method to the URL passing
	// the callback functions to handle the response
	SendPayload(TEXT("edits"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
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
				OnFailure.Broadcast(FCreateEditsResponse(), ResponseString, ErrorMessage);
				return;
			}

			// Convert the response to a struct and check if it was successful
			FCreateEditsResponse EditsResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EditsResponse, 0, 0))
			{
				// If it was, broadcast the success event with the response
				OnSuccess.Broadcast(EditsResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				// If it wasn't, broadcast the failure event with the error message
				OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Failed to convert create edits response to struct"));
			}
		}
		else
		{
			// If the request wasn't successful, broadcast the failure event with the
			// error message 
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Create edits request failed"));
		}
	}, [this]
	{
			// If the request failed to send, broadcast the failure event with the error
			// message
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Failed to send create edits request"));
	});
}

#pragma endregion