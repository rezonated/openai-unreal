#pragma once
#include "UnrealOpenAI.h"
#include "Config/UnrealOpenAIConfig.h"

static const FString BaseURL = TEXT("https://api.openai.com/v1/");

static void PrintDebugOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}

static void PrintDebugLog(const FString& Message)
{
	UE_LOG(LogTypeOpenAI, Warning, TEXT("%s"), *Message);
}

static void PrintDebugLogAndOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	PrintDebugLog(Message);
	PrintDebugOnScreen(Message, Duration, Color);
}

static FString SanitizeString(const FString& String)
{
	FString SanitizedString = String;
	SanitizedString.ReplaceInline(TEXT("\n"), TEXT(""));
	SanitizedString.ReplaceInline(TEXT("\r"), TEXT(""));
	SanitizedString.ReplaceInline(TEXT("\t"), TEXT(""));
	return SanitizedString;
}

static void SendPayload(FString PayloadURL, FString JSONPayload, TFunction<void(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)> OnComplete, TFunction<void()> OnFailed)
{
	const auto HTTP = &FHttpModule::Get();

	if (!HTTP) return;

	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->SetURL(BaseURL + PayloadURL);
	HTTPRequest->SetVerb(TEXT("POST"));
	HTTPRequest->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	HTTPRequest->SetHeader("Content-Type", TEXT("application/json"));

	if (const auto PluginSettings = GetMutableDefault<UUnrealOpenAIConfig>())
	{
		HTTPRequest->SetHeader("OpenAI-Organization", PluginSettings->Organization);
		HTTPRequest->SetHeader("Authorization", TEXT("Bearer ") + PluginSettings->APIKey);
	}

	HTTPRequest->SetContentAsString(JSONPayload);

	HTTPRequest->OnProcessRequestComplete().BindLambda([OnComplete] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		OnComplete(Request, Response, bWasSuccessful);
	});

	if (!HTTPRequest->ProcessRequest())
	{
		OnFailed();
	}
}