﻿// Fill out your copyright notice in the Description page of Project Settings.


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
			const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseString);
			
			if (TSharedPtr<FJsonObject> JSONObject; FJsonSerializer::Deserialize(Reader, JSONObject))
			{
				PrintDebugLog(Response->GetContentAsString());
				
				if (FString IdPayload = ""; JSONObject->TryGetStringField("id", IdPayload))
				{
					Id = IdPayload;
				}
				if (FString ObjectPayload = ""; JSONObject->TryGetStringField("object", ObjectPayload))
				{
					Object = ObjectPayload;
				}
				if (uint64 CreatedPayload; JSONObject->TryGetNumberField("created", CreatedPayload))
				{
					Created = FString::FromInt(CreatedPayload);
				}

				if (FString ModelPayload = ""; JSONObject->TryGetStringField("model", ModelPayload))
				{
					Model = ModelPayload;
				}

				FChoice ChoicePayload;
				const TSharedPtr<FJsonObject> ChoiceObject = 
				JSONObject->GetArrayField("choices")[0]->AsObject();
				FJsonObjectConverter::JsonObjectToUStruct(ChoiceObject.ToSharedRef(), &ChoicePayload, 0, 0);
				Choices = ChoicePayload;

				FUsage UsagePayload;
				const TSharedPtr<FJsonObject> UsageObject = JSONObject->GetObjectField("usage");
				FJsonObjectConverter::JsonObjectToUStruct(UsageObject.ToSharedRef(), &UsagePayload, 0, 0);

				OnCompletionRequestComplete.Broadcast(Id, Object, Created, Model, Choices, Usage);
			}
			else
			{
				OnCompletionRequestFailed.Broadcast(TEXT(""), TEXT(""), TEXT(""), TEXT(""), FChoice(), FUsage());
			}
		}
		else
		{
			OnCompletionRequestFailed.Broadcast(TEXT(""), TEXT(""), TEXT(""), TEXT(""), FChoice(), FUsage());
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
	JSONRequest->SetStringField("prompt", Prompt);
	JSONRequest->SetNumberField("max_tokens", 128);
	JSONRequest->SetStringField("model", CompletionModels[static_cast<int>(CompletionModel)]);
	JSONRequest->SetNumberField("temperature", 0.f);
	const TSharedRef< TJsonWriter<> > Writer = TJsonWriterFactory<>::Create(&JSONPayload);
	FJsonSerializer::Serialize(JSONRequest.ToSharedRef(), Writer);
	
	HTTPRequest->SetContentAsString(JSONPayload);
	

	if (!HTTPRequest->ProcessRequest())
	{
		OnCompletionRequestFailed.Broadcast(TEXT(""), TEXT(""), TEXT(""), TEXT(""), FChoice(), FUsage());
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
