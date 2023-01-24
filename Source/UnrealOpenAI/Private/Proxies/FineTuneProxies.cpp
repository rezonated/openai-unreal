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
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (TrainingFileID.IsEmpty() || TrainingFileID == TEXT("") || TrainingFileID.Len() <= 0)
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("TrainingFileID is empty"));
	}

	if (ValidationFileID.IsEmpty() || ValidationFileID == TEXT("") || ValidationFileID.Len() <= 0)
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("ValidationFileID is empty"));
	}

	if (Model == EFineTuneModels::EFTM_MAX)
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Model is invalid"));
	}

	FString JSONPayload;

	FCreateFineTuneRequest RequestPayload;

	if (!ValidationFileID.IsEmpty())
	{
		RequestPayload.validation_file = ValidationFileID;	
	}
	
	RequestPayload.training_file = TrainingFileID;
	RequestPayload.model = FineTuneModels[static_cast<int32>(Model)];

	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("fine-tunes"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FFineTune(), ResponseString, ErrorMessage);
				return;
			}
			
			FFineTune FineTuneResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &FineTuneResponse, 0, 0))
			{
				OnSuccess.Broadcast(FineTuneResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to convert create fine tune response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Create fine tune request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to send create fine tune request"));
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
		OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	SendPayload(TEXT("fine-tunes"), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FListFineTunesResponse(), ResponseString, ErrorMessage);
				return;
			}
				
			FListFineTunesResponse ListFineTunesResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFineTunesResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFineTunesResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""), TEXT("Failed to convert list fine tune response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""), TEXT("List fine tune request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FListFineTunesResponse(), TEXT(""), TEXT("Failed to send list fine tune request"));
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
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FineTuneID.IsEmpty() || FineTuneID == TEXT("") || FineTuneID.Len() <= 0)
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("FineTuneID is empty"));
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
				OnSuccess.Broadcast(FineTuneResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to convert retrieve fine tune response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Retrieve fine tune request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to send retrieve fine tune request"));
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
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FineTuneID.IsEmpty() || FineTuneID == TEXT("") || FineTuneID.Len() <= 0)
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("FineTuneID is empty"));
	}

	SendPayload(FString::Printf(TEXT("fine-tunes/%s/cancel"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FFineTune(), ResponseString, ErrorMessage);
				return;
			}
				
			FFineTune FineTuneResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &FineTuneResponse, 0, 0))
			{
				OnSuccess.Broadcast(FineTuneResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to convert cancel fine tune response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Cancel fine tune request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FFineTune(), TEXT(""), TEXT("Failed to send cancel fine tune request"));
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
		OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FineTuneID.IsEmpty() || FineTuneID == TEXT("") || FineTuneID.Len() <= 0)
	{
		OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""), TEXT("FineTuneID is empty"));
	}

	SendPayload(FString::Printf(TEXT("fine-tunes/%s/events?stream=false"), *FineTuneID), TEXT(""), EHTTPMethod::EHP_GET, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FListFineTuneEventsResponse(), ResponseString, ErrorMessage);
				return;
			}
				
			FListFineTuneEventsResponse ListFineTuneEventsResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ListFineTuneEventsResponse, 0, 0))
			{
				OnSuccess.Broadcast(ListFineTuneEventsResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""), TEXT("Failed to convert fine tune events response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""), TEXT("Fine tune events request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FListFineTuneEventsResponse(), TEXT(""), TEXT("List fine tune events request failed"));
	});
}

UDeleteFineTuneModelProxy* UDeleteFineTuneModelProxy::DeleteFineTuneModel(UObject* WorldContextObject,
	FString ModelFineTuneID)
{ 
	UDeleteFineTuneModelProxy* Proxy = NewObject<UDeleteFineTuneModelProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->ModelFineTuneID = ModelFineTuneID;
	return Proxy;
}

void UDeleteFineTuneModelProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	SendPayload(FString::Printf(TEXT("models/%s"), *ModelFineTuneID), TEXT(""), EHTTPMethod::EHP_DELETE, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FDeleteResponse(), ResponseString, ErrorMessage);
				return;
			}
				
			FDeleteResponse DeleteResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &DeleteResponse, 0, 0))
			{
				OnSuccess.Broadcast(DeleteResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Failed to convert delete fine tune model response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Delete fine tune model request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FDeleteResponse(), TEXT(""), TEXT("Failed to send delete fine tune model request"));
	});
}



