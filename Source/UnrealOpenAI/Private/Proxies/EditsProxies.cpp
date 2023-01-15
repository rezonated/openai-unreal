// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/EditsProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

UCreateEditsProxies* UCreateEditsProxies::CreateEdits(UObject* WorldContextObject, FString Input, FString Instruction)
{
	UCreateEditsProxies* Proxy = NewObject<UCreateEditsProxies>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	Proxy->Instruction = Instruction;
	return Proxy;
}

void UCreateEditsProxies::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""));
		return;
	}

	FString JSONPayload;
	FCreateEditsRequest RequestPayload;
	RequestPayload.input = Input;
	RequestPayload.instruction = Instruction;

	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("edits"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FCreateEditsResponse EditsResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EditsResponse, 0, 0))
			{
				OnSuccess.Broadcast(EditsResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""));
	});
}
