// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "Engine/Classes/Engine/Texture2D.h"
#include "Engine/Public/ImageUtils.h"
#include "HttpModule.h"
#include "JsonObjectConverter.h"
#include "UnrealOpenAI.h"
#include "Config/UnrealOpenAIConfig.h"
#include "Constants/UtilsConstants.h"
#include "Enums/UtilsEnums.h"
#include "Interfaces/IHttpRequest.h"

/**
 * Print a message on the screen
 * @param Message Message to print
 * @param Duration Duration to display the message
 * @param Color Color of the message
 */
static void PrintDebugOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	// Gets the engine pointer to print the message on the screen
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}

/**
 * Print a message into the log using LogTypeOpenAI
 * @param Message Message to print
 */
static void PrintDebugLog(const FString& Message)
{
	// Log the message into the log using LogTypeOpenAI
	UE_LOG(LogTypeOpenAI, Display, TEXT("%s"), *Message);
}

/**
 * Print a message into the log using LogTypeOpenAI and on the screen
 * @param Message Message to print
 * @param Duration Duration to display the message
 * @param Color Color of the message
 */
static void PrintDebugLogAndOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	// Log the message into the log using LogTypeOpenAI and on the screen
	PrintDebugLog(Message);
	PrintDebugOnScreen(Message, Duration, Color);
}

/**
 * Sanitize a string by removing new lines, carriage returns and tabs
 * @param String String to sanitize
 * @return Sanitized string
 */
static FString SanitizeString(const FString& String)
{
	FString SanitizedString = String;

	// Remove new lines, 
	SanitizedString.ReplaceInline(TEXT("\n"), TEXT(""));
	// Remove carriage returns 
	SanitizedString.ReplaceInline(TEXT("\r"), TEXT(""));
	// Remove tabs
	SanitizedString.ReplaceInline(TEXT("\t"), TEXT(""));
	
	return SanitizedString;
}

/**
 * Convert a string to bytes
 * @param InString String to convert to bytes
 * @return Bytes from the string
 */
static TArray<uint8> FStringToUInt8(const FString& InString)
{
	TArray<uint8> OutBytes;

	// Check if the string is not empty
	if (InString.Len() > 0)
	{
		// Convert the string to bytes by using the FTCHARToUTF8 and
		// then append the bytes to the array
		const FTCHARToUTF8 Converted(*InString);
		OutBytes.Append(reinterpret_cast<const uint8*>(Converted.Get()), Converted.Length());
	}

	// Return the bytes
	return OutBytes;
}

/**
 * Adds new field for multipart/form-data request
 * @param Name Name of the data
 * @param Value Value of the data
 * @return String containing the data
 */
static FString AddData(FString Name, FString Value) {
	// Return a new field for multipart/form-data request with the name and value by adding boundary for begin, content disposition and value
	return FString(TEXT("\r\n"))
		+ BoundaryBegin
		+ FString(TEXT("Content-Disposition: form-data; name=\""))
		+ Name
		+ FString(TEXT("\"\r\n\r\n"))
		+ Value;
}

/**
 * Validates the target image for OpenAI Image API
 * Validates that the image is square and that the size is within the limit
 * @param ImageData Bytes of the image to validate
 * @param OutReasonInvalid Reason why the image is invalid if any
 * @return true if the image is valid
 */
static bool ValidateImageForOpenAI(TArray<uint8> ImageData, FString& OutReasonInvalid)
{
	// Check if the image size is within the limit
	if (ImageData.Num() >= OPENAI_FILE_SIZE_LIMIT)
	{
		// Set the reason the image is invalid because it is too large
		OutReasonInvalid = "Image size is too large. Please use a smaller image.";
		return false;
	}

	// Check if the image size is too small
	if (ImageData.Num() <= 0)
	{
		// Set the reason the image is invalid because it is too small
		OutReasonInvalid = "Image size is too small. Please use a larger image.";
		return false;
	}

	// Check if the image is square
	if (const UTexture2D* ImageBuffer = FImageUtils::ImportBufferAsTexture2D(ImageData); ImageBuffer->GetSizeX() != ImageBuffer->GetSizeY())
	{
		// Set the reason the image is invalid because it is not square
		OutReasonInvalid = "Image is not square. Please use a square image.";
		return false;
	}
	
	return true;
}

/**
 * Send a payload to the URL, using the specified method containing the JSON payload.
 * Pass a callback for when the request is completed and one for when the request failed.
 * @param PayloadURL URL to send the payload to
 * @param JSONPayload JSON payload to send
 * @param Method HTTP method to use
 * @param OnComplete On complete callback
 * @param OnFailed On failed callback
 */
static void SendPayload(FString PayloadURL, FString JSONPayload, EHTTPMethod Method, TFunction<void(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)> OnComplete, TFunction<void()> OnFailed)
{
	// Get the HTTP module and check if it is valid
	const auto HTTP = &FHttpModule::Get();
	if (!HTTP)
	{
		// If not, call the failed callback and return
		OnFailed();
		return;
	}

	// Create a new HTTP request, set the URL, verb, headers and content as the JSON
	// payload
	const auto HTTPRequest = HTTP->CreateRequest();
	HTTPRequest->SetURL(BaseURL + PayloadURL);
	HTTPRequest->SetVerb(HTTPMethods[static_cast<int>(Method)]);
	HTTPRequest->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	HTTPRequest->SetHeader("Content-Type", TEXT("application/json"));

	// Get the plugin settings and check if it is valid
	if (const auto PluginSettings = GetMutableDefault<UUnrealOpenAIConfig>())
	{
		// If it is, set the organization and API key headers
		HTTPRequest->SetHeader("OpenAI-Organization", PluginSettings->Organization);
		HTTPRequest->SetHeader("Authorization", TEXT("Bearer ") + PluginSettings->APIKey);
	}

	// Set the content as the JSON payload and bind the on complete callback
	HTTPRequest->SetContentAsString(JSONPayload);
	HTTPRequest->OnProcessRequestComplete().BindLambda([OnComplete] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		OnComplete(Request, Response, bWasSuccessful);
	});

	// Process the request and check if it was successful
	if (!HTTPRequest->ProcessRequest())
	{
		// If not, call the failed callback
		OnFailed();
	}
}

/**
 * Send a payload to the URL, using the specified method containing the
 * multipart/form-data payload. Pass a callback for when the request is completed and one
 * for when the request failed.
 * @param PayloadURL URL to send the payload to
 * @param ContentPayload multipart/form-data payload to send
 * @param Method HTTP method to use
 * @param OnComplete On complete callback
 * @param OnFailed On failed callback
 */
static void SendPayloadMultipartFormData(FString PayloadURL, TArray<uint8> ContentPayload, EHTTPMethod Method, TFunction<void(FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)> OnComplete, TFunction<void()> OnFailed)
{
	// Get the HTTP module and check if it is valid
	const auto HTTP = &FHttpModule::Get();
	if (!HTTP)
	{
		// If not, call the failed callback and return
		OnFailed();
		return;
	}

	// Create a new HTTP request, set the URL, verb, headers and content as the
	// multipart/form-data payload
	const auto HTTPRequest = HTTP->CreateRequest();
	HTTPRequest->SetURL(BaseURL + PayloadURL);
	HTTPRequest->SetVerb(HTTPMethods[static_cast<int>(Method)]);
	HTTPRequest->SetHeader("User-Agent", "X-UnrealEngine-Agent");
	HTTPRequest->SetHeader(TEXT("Content-Type"), FString(TEXT("multipart/form-data; boundary=")) + BoundaryLabel);

	// Get the plugin settings and check if it is valid
	if (const auto PluginSettings = GetMutableDefault<UUnrealOpenAIConfig>())
	{
		// If it is, set the organization and API key headers
		HTTPRequest->SetHeader("OpenAI-Organization", PluginSettings->Organization);
		HTTPRequest->SetHeader("Authorization", TEXT("Bearer ") + PluginSettings->APIKey);
	}

	// Bind the on complete callback
	HTTPRequest->OnProcessRequestComplete().BindLambda([OnComplete] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		OnComplete(Request, Response, bWasSuccessful);
	});

	// Set the content as the multipart/form-data payload and process the request
	HTTPRequest->SetContent(ContentPayload);
	if (!HTTPRequest->ProcessRequest())
	{
		// If the request was not successful, call the failed callback
		OnFailed();
	}
}

/**
 * Check if the passed response contains an error, if so, return the error message and type
 * Used for handling error from OpenAI API responses
 * @param JSONResponseString JSON response string to parse 
 * @param ErrorMessage Error message to return if any
 * @param ErrorType Error type to return if any
 * @return true if the passed response contains an error
 */
static bool CheckErrorResponse(FString JSONResponseString, FString& ErrorMessage, FString& ErrorType)
{
	// Create a new error response struct and convert the JSON response string to it
	FErrorResponse ErrorResponse;
	FJsonObjectConverter::JsonObjectStringToUStruct(JSONResponseString, &ErrorResponse, 0, 0);

	// Check if the error message or type is not empty, if so, set the error message and
	// type and return true
	if (!ErrorResponse.error.message.IsEmpty() || !ErrorResponse.error.type.IsEmpty())
	{
		ErrorMessage = ErrorResponse.error.message;
		ErrorType = ErrorResponse.error.type;
		return true;
	}

	// If there is no error, return false
	return false;
}