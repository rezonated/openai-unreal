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

UListFineTuneProxy* UListFineTuneProxy::ListFineTune(UObject* WorldContextObject)
{
	UListFineTuneProxy* Proxy = NewObject<UListFineTuneProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}

void UListFineTuneProxy::Activate()
{
	Super::Activate();
	
	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""));
		return;
	}

	SendPayload(TEXT("fine-tunes"), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FListFineTunesResponse ListFineTunesResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFineTunesResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFineTunesResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""));
	});
}

URetrieveFineTuneProxy* URetrieveFineTuneProxy::RetrieveFineTune(UObject* WorldContextObject, FString FineTuneID)
{ 
	URetrieveFineTuneProxy* Proxy = NewObject<URetrieveFineTuneProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FineTuneID = FineTuneID;
	return Proxy;
}

void URetrieveFineTuneProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FFineTune(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("fine-tunes/%s"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
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

UCancelFineTuneProxy* UCancelFineTuneProxy::CancelFineTune(UObject* WorldContextObject, FString FineTuneID)
{
	UCancelFineTuneProxy* Proxy = NewObject<UCancelFineTuneProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FineTuneID = FineTuneID;
	return Proxy;
}

void UCancelFineTuneProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FFineTune(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("fine-tunes/%s/cancel"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
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

UListFineTuneEventsProxy* UListFineTuneEventsProxy::ListFineTuneEvents(UObject* WorldContextObject,
	FString FineTuneID)
{ 
	UListFineTuneEventsProxy* Proxy = NewObject<UListFineTuneEventsProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FineTuneID = FineTuneID;
	return Proxy;
}

void UListFineTuneEventsProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("fine-tunes/%s/events?stream=false"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FListFineTuneEventsResponse ListFineTuneEventsResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFineTuneEventsResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFineTuneEventsResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""));
	});
}

UDeleteFineTuneModelProxy* UDeleteFineTuneModelProxy::DeleteFineTuneModel(UObject* WorldContextObject,
	FString FineTuneID)
{ 
	UDeleteFineTuneModelProxy* Proxy = NewObject<UDeleteFineTuneModelProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->FineTuneID = FineTuneID;
	return Proxy;
}

void UDeleteFineTuneModelProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
		return;
	}

	SendPayload(FString::Printf(TEXT("models/%s"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_DELETE, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);
				
			FDeleteResponse DeleteResponse;
				
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &DeleteResponse, 0, 0))
			{
				OnSuccess.Broadcast(DeleteResponse, Response->GetContentAsString());
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
				OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""));
	});
}



