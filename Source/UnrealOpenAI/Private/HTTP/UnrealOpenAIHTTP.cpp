// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/UnrealOpenAIHTTP.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "UnrealOpenAI/Public/Utils.h"

void UUnrealOpenAIHTTPCompletionRequest::Activate()
{
	Super::Activate();

	if (!WorldContextObject) return;	

	FString JSONPayload;
	const FCreateCompletionRequest RequestPayload
	{
		CompletionModels[static_cast<int>(CompletionModel)],
		Prompt
	};
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
	
	SendPayload(
		TEXT("completions"),
		JSONPayload,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);
				
				FCreateCompletionResponse CompletionResponse;
				
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CompletionResponse, 0, 0))
				{
					OnCompletionRequestComplete.Broadcast(CompletionResponse, Response->GetContentAsString());
				}
				else
				{
					OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
				}
			}
			else
			{
				OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
			}
	},
	[this]{
			OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
		}
	);
}

UUnrealOpenAIHTTPCompletionRequest* UUnrealOpenAIHTTPCompletionRequest::CreateCompletion(UObject* WorldContextObject,
	FString Prompt, ECompletionModel CompletionModel)
{
	UUnrealOpenAIHTTPCompletionRequest* CompletionRequest = NewObject<UUnrealOpenAIHTTPCompletionRequest>();
	CompletionRequest->WorldContextObject = WorldContextObject;
	CompletionRequest->Prompt = Prompt;
	CompletionRequest->CompletionModel = CompletionModel;
	return CompletionRequest;
}
