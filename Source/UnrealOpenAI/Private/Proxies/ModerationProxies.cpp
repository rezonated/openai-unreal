// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/ModerationProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Moderation Proxies

UCreateModerationRequestProxy* UCreateModerationRequestProxy::CreateModerationRequest(UObject* WorldContextObject, FString Input, EModerationModels Model)
{
	UCreateModerationRequestProxy* Proxy = NewObject<UCreateModerationRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	Proxy->Model = Model;
	return Proxy;
}

void UCreateModerationRequestProxy::Activate()
{
	Super::Activate();
	
	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Input is empty"));
	}

	FString JSONPayload;
	FCreateModerationRequest RequestPayload;
	RequestPayload.input = Input;
	RequestPayload.model = ModerationModels[static_cast<int>(Model)];
	
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
	
	SendPayload(
		TEXT("moderations"),
		JSONPayload, EHTTPMethod::EHP_POST,
			[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					OnFailure.Broadcast(FCreateModerationResponse(), ResponseString, ErrorMessage);
					return;
				}
				
				FCreateModerationResponse ModerationResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ModerationResponse, 0, 0))
				{
					OnSuccess.Broadcast(ModerationResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Failed to convert create moderation response to struct"));
				}
			}
			else
			{
				OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Create moderation request failed"));
			}
	},
	[this]
	{
			OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""), TEXT("Failed to send create moderation request"));
		}
	);
}

#pragma endregion