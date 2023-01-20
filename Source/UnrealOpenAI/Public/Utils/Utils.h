// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "Engine/Classes/Engine/Texture2D.h"
#include "Engine/Public/ImageUtils.h"
#include "HttpModule.h"
#include "UnrealOpenAI.h"
#include "Config/UnrealOpenAIConfig.h"
#include "Constants/UtilsConstants.h"
#include "Enums/UtilsEnums.h"
#include "Interfaces/IHttpRequest.h"

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

static TArray<uint8> FStringToUInt8(const FString& InString)
{
	TArray<uint8> OutBytes;
	
	if (InString.Len() > 0)
	{
		const FTCHARToUTF8 Converted(*InString);
		OutBytes.Append(reinterpret_cast<const uint8*>(Converted.Get()), Converted.Length());
	}
	return OutBytes;
}

static FString AddData(FString Name, FString Value) {
	return FString(TEXT("\r\n"))
		+ BoundaryBegin
		+ FString(TEXT("Content-Disposition: form-data; name=\""))
		+ Name
		+ FString(TEXT("\"\r\n\r\n"))
		+ Value;
}

static bool ValidateImageForOpenAI(TArray<uint8> ImageData, FString& OutReasonInvalid)
{
	if (ImageData.Num() >= OPENAI_FILE_SIZE_LIMIT)
	{
		OutReasonInvalid = "Image size is too large. Please use a smaller image.";
		return false;
	}

	if (ImageData.Num() <= 0)
	{
		OutReasonInvalid = "Image size is too small. Please use a larger image.";
		return false;
	}
	
	if (const UTexture2D* ImageBuffer = FImageUtils::ImportBufferAsTexture2D(ImageData); ImageBuffer->GetSizeX() != ImageBuffer->GetSizeY())
	{
		OutReasonInvalid = "Image is not square. Please use a square image.";
		return false;
	}
	
	return true;
}

static void SendPayload(FString PayloadURL, FString JSONPayload, EHTTPMethod Method, TFunction<void(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)> OnComplete, TFunction<void()> OnFailed)
{
	const auto HTTP = &FHttpModule::Get();

	if (!HTTP)
	{
		OnFailed();
		return;
	}
	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->SetURL(BaseURL + PayloadURL);
	
	HTTPRequest->SetVerb(HTTPMethods[static_cast<int>(Method)]);
	
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

static void SendPayloadMultipartFormData(FString PayloadURL, TArray<uint8> ContentPayload, EHTTPMethod Method, TFunction<void(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)> OnComplete, TFunction<void()> OnFailed)
{
	const auto HTTP = &FHttpModule::Get();
	
	if (!HTTP)
	{
		OnFailed();
		return;
	}
	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->SetURL(BaseURL + PayloadURL);
	
	HTTPRequest->SetVerb(HTTPMethods[static_cast<int>(Method)]);
	
	HTTPRequest->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	HTTPRequest->SetHeader(TEXT("Content-Type"), FString(TEXT("multipart/form-data; boundary=")) + BoundaryLabel);

	if (const auto PluginSettings = GetMutableDefault<UUnrealOpenAIConfig>())
	{
		HTTPRequest->SetHeader("OpenAI-Organization", PluginSettings->Organization);
		HTTPRequest->SetHeader("Authorization", TEXT("Bearer ") + PluginSettings->APIKey);
	}

	HTTPRequest->OnProcessRequestComplete().BindLambda([OnComplete] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		OnComplete(Request, Response, bWasSuccessful);
	});

	HTTPRequest->SetContent(ContentPayload);

	if (!HTTPRequest->ProcessRequest())
	{
		OnFailed();
	}
}

static bool CheckErrorResponse(FString JSONResponseString, FString& ErrorMessage, FString& ErrorType)
{
	FErrorResponse ErrorResponse;

	FJsonObjectConverter::JsonObjectStringToUStruct(JSONResponseString, &ErrorResponse, 0, 0);

	if (!ErrorResponse.error.message.IsEmpty() || !ErrorResponse.error.type.IsEmpty())
	{
		ErrorMessage = ErrorResponse.error.message;
		ErrorType = ErrorResponse.error.type;
		return true;
	}

	return false;
}