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
	UCreateCompletionRequestProxy* CompletionRequest = NewObject<UCreateCompletionRequestProxy>();
	CompletionRequest->WorldContextObject = WorldContextObject;
	CompletionRequest->Prompt = Prompt;
	CompletionRequest->CompletionModel = CompletionModel;
	return CompletionRequest;
}

void UCreateCompletionRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Prompt.IsEmpty() || Prompt == TEXT("") || Prompt.Len() <= 0)
	{
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}

	if (CompletionModel == ECompletionModel::ECM_MAX)
	{
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("CompletionModel is invalid"));
		return;	
	}

	FString JSONPayload;
	FCreateCompletionRequest RequestPayload;
	RequestPayload.model = CompletionModels[static_cast<int>(CompletionModel)];
	RequestPayload.prompt = Prompt;
	
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
	
	SendPayload(
		TEXT("completions"),
		JSONPayload, EHTTPMethod::EHP_POST,
			[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);
				
				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					OnFailure.Broadcast(FCreateCompletionResponse(), ResponseString, ErrorMessage);
					return;
				}
				
				FCreateCompletionResponse CreateCompletionResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateCompletionResponse, 0, 0))
				{
					OnSuccess.Broadcast(CreateCompletionResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Failed to convert create completion response to struct"));
				}
			}
			else
			{
				OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Create completion request failed"));
			}
	},
	[this]
	{
			OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""), TEXT("Failed to send create completion request"));
		}
	);
}

#pragma endregion