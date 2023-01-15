// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/ModerationProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

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
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""));
		return;
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
				
				FCreateModerationResponse ModerationResponse;
				
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ModerationResponse, 0, 0))
				{
					OnSuccess.Broadcast(ModerationResponse, Response->GetContentAsString());
				}
				else
				{
					PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
					OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""));
				}
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to complete completion request");
				OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""));
			}
	},
	[this]
	{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateModerationResponse(), TEXT(""));
		}
	);
}
