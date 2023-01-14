// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/UnrealOpenAIHTTP.h"

#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "Config/UnrealOpenAIConfig.h"
#include "Interfaces/IHttpResponse.h"
#include "UnrealOpenAI/Public/Utils.h"

void UUnrealOpenAIHTTPCompletionRequest::Activate()
{
	Super::Activate();

	if (!WorldContextObject) return;

	const auto HTTP = &FHttpModule::Get();

	if (!HTTP) return;

	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->OnProcessRequestComplete().BindLambda([this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = ResponseString.Replace(TEXT("\n"), TEXT(""));
			ResponseString = ResponseString.Replace(TEXT("\r"), TEXT(""));
			ResponseString = ResponseString.Replace(TEXT("\t"), TEXT(""));
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
	});

	HTTPRequest->SetURL(BaseURL + TEXT("completions"));
	HTTPRequest->SetVerb(TEXT("POST"));
	HTTPRequest->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	HTTPRequest->SetHeader("Content-Type", TEXT("application/json"));

	if (const auto PluginSettings = GetMutableDefault<UUnrealOpenAIConfig>())
	{
		HTTPRequest->SetHeader("OpenAI-Organization", PluginSettings->Organization);
		HTTPRequest->SetHeader("Authorization", TEXT("Bearer ") + PluginSettings->APIKey);
	}

	FString JSONPayload;
	const TSharedPtr<FJsonObject> JSONRequest = MakeShareable(new FJsonObject());
	FCreateCompletionRequest RequestPayload;
	RequestPayload.prompt = Prompt;
	RequestPayload.max_tokens = 1000;
	RequestPayload.model = CompletionModels[static_cast<int>(CompletionModel)];
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);
	
	HTTPRequest->SetContentAsString(JSONPayload);
	

	if (!HTTPRequest->ProcessRequest())
	{
		OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
	}
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
