// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/ChatProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

UChatProxies* UChatProxies::Chat(UObject* WorldContextObject, FString Model, TArray<FMessage> Messages)
{
	// Create a new proxy object and set the parameters, then
	// return it
	UChatProxies* Proxy = NewObject<UChatProxies>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Model = Model;
	Proxy->Messages = Messages;
	return Proxy;
}

void UChatProxies::Activate()
{
	Super::Activate();

	// Check if the WorldContextObject is valid
	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	// Check if the Model is valid
	if (Model.IsEmpty() || Model == TEXT("") || Model.Len() <= 0)
	{
		OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("Model is empty"));
		return;
	}

	// Check if the Messages is valid
	if (Messages.Num() <= 0)
	{
		OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("Messages is empty"));
		return;
	}

	// Create the struct payload and FString to store the
	// converted JSON 
	FString JSONPayload;
	FChatRequest RequestPayload;
	RequestPayload.model = Model;
	RequestPayload.messages = Messages;

	// Convert the struct to JSON
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
		
	// Send the request containing the JSON payload using POST method to the URL passing
	// the callback functions to handle the response 
	SendPayload(
		TEXT("chat/completions"),
		JSONPayload,
		EHTTPMethod::EHP_POST,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
				// Check if the request was successful
			if (bWasSuccessful)
			{
				// Get the response as a string and sanitize it
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				PrintDebugLog("Chat Response: " + ResponseString);

				// Check if the response contains an error
				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					// If it does, broadcast the error message
					OnFailure.Broadcast(FChatResponse(), ResponseString, ErrorMessage);
					return;
				}

				// Convert the response to a struct and check if it was successful
				FChatResponse ChatResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ChatResponse, 0, 0))
				{
					// If it was, broadcast the response
					OnSuccess.Broadcast(ChatResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					// If it wasn't, broadcast the error message
					OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("Failed to convert create completion response to struct"));
				}
			}
			else
			{
				// If the request wasn't successful, broadcast the error message
				OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("Create completion request failed"));
			}
	},
	[this]
	{
			// If the request failed to send, broadcast the error message
			OnFailure.Broadcast(FChatResponse(), TEXT(""), TEXT("Failed to send create completion request"));
		}	
	);
}
