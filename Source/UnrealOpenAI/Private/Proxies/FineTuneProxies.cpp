// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/FineTuneProxies.h"

#include "JsonObjectConverter.h"
#include "Constants/FineTuneConstants.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"


UCreateFineTuneProxy* UCreateFineTuneProxy::CreateFineTune(UObject* WorldContextObject, FString TrainingFileID,
	FString ValidationFileID, EFineTuneModels Model)
{
	UCreateFineTuneProxy* Proxy = NewObject<UCreateFineTuneProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->TrainingFileID = TrainingFileID;
	Proxy->ValidationFileID = ValidationFileID;
	Proxy->Model = Model;
	return Proxy;
}

void UCreateFineTuneProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FFineTune(), TEXT(""));
		return;
	}

	FString JSONPayload;

	FCreateFineTuneRequest RequestPayload;

	if (!ValidationFileID.IsEmpty())
	{
		RequestPayload.validation_file = ValidationFileID;	
	}
	
	RequestPayload.training_file = TrainingFileID;
	RequestPayload.model = FineTuneModels[static_cast<int32>(Model)];

	PrintDebugLogAndOnScreen(RequestPayload.training_file);

	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	PrintDebugLogAndOnScreen(JSONPayload);

	SendPayload(TEXT("fine-tunes"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FFineTune FineTuneResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &FineTuneResponse, 0, 0))
			{
				OnSuccess.Broadcast(FineTuneResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FFineTune(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FFineTune(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FFineTune(), TEXT(""));
	});
}


