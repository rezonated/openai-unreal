// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/CompletionProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Completion Proxy

UCreateCompletionProxies* UCreateCompletionProxies::CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel)
{
	UCreateCompletionProxies* CompletionRequest = NewObject<UCreateCompletionProxies>();
	CompletionRequest->WorldContextObject = WorldContextObject;
	CompletionRequest->Prompt = Prompt;
	CompletionRequest->CompletionModel = CompletionModel;
	return CompletionRequest;
}

void UCreateCompletionProxies::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""));
		return;
	}

	FString JSONPayload;
	const FCreateCompletionRequest RequestPayload
	{
		CompletionModels[static_cast<int>(CompletionModel)],
		Prompt
	};
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
	
	SendPayload(
		TEXT("completions"),
		JSONPayload, EHTTPMethod::EHP_POST,
			[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);
				
				FCreateCompletionResponse CompletionResponse;
				
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CompletionResponse, 0, 0))
				{
					OnSuccess.Broadcast(CompletionResponse, Response->GetContentAsString());
				}
				else
				{
					PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
					OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""));
				}
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to complete completion request");
				OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""));
			}
	},
	[this]
	{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
			OnFailure.Broadcast(FCreateCompletionResponse(), TEXT(""));
		}
	);
}

#pragma endregion