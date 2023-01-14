// Fill out your copyright notice in the Description page of Project Settings.


#include "HTTP/UnrealOpenAIHTTP.h"

#include "JsonObjectConverter.h"
#include "Constants/Constants.h"
#include "Interfaces/IHttpResponse.h"
#include "UnrealOpenAI/Public/Utils/Utils.h"

void UUnrealOpenAIHTTPCompletionRequest::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
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
		JSONPayload, EHTTPMethod::ECM_POST,
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
					PrintDebugLogAndOnScreen("Failed to convert completion JSON response to struct");
					OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
				}
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to complete completion request");
				OnCompletionRequestFailed.Broadcast(FCreateCompletionResponse(), TEXT(""));
			}
	},
	[this]
	{
			PrintDebugLogAndOnScreen("Failed to complete completion request");
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

void UUnrealOpenAIHTTPImageVariationRequestURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");

		OnImageVariationRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(Image, InvalidReason))
	{
		PrintDebugLogAndOnScreen(InvalidReason);

		OnImageVariationRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	FCreateImageVariationRequest RequestPayload;
	RequestPayload.image = Image;
	RequestPayload.response_format = "url";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  filename=\"image.png\"\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(Image);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/variations", CombinedContent, EHTTPMethod::ECM_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseURL CreateImageVariationResponseURL;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseURL, 0, 0))
			{
				OnImageVariationRequestCompleteURL.Broadcast(CreateImageVariationResponseURL, Response->GetContentAsString());
			}else
			{
				PrintDebugLogAndOnScreen("Failed to parse response to URL struct.");
				OnImageVariationRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete image variation request");
			OnImageVariationRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to process image variation request");
		OnImageVariationRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
	});
}

UUnrealOpenAIHTTPImageVariationRequestURL* UUnrealOpenAIHTTPImageVariationRequestURL::CreateImageVariationURL(
	UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize)
{
	UUnrealOpenAIHTTPImageVariationRequestURL* ImageVariationRequest = NewObject<UUnrealOpenAIHTTPImageVariationRequestURL>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->Image = Image;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UUnrealOpenAIHTTPImageVariationRequestBase64JSON::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");

		OnImageVariationRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	if(FString ReasonInvalid; !ValidateImageForOpenAI(Image, ReasonInvalid))
	{
		PrintDebugLogAndOnScreen(ReasonInvalid);

		OnImageVariationRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}
	
	FCreateImageVariationRequest RequestPayload;
	RequestPayload.image = Image;
	RequestPayload.response_format = "b64_json";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  filename=\"image.png\"\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(Image);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/variations", CombinedContent, EHTTPMethod::ECM_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseBase64JSON CreateImageVariationResponseBase64JSON;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseBase64JSON, 0, 0))
			{
				OnImageVariationRequestCompleteBase64JSON.Broadcast(CreateImageVariationResponseBase64JSON, Response->GetContentAsString());
			}else
			{
				PrintDebugLogAndOnScreen("Failed to parse response to JSON struct.");
				OnImageVariationRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete image variation request");
			OnImageVariationRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to process image variation request");
		OnImageVariationRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
	});
}

UUnrealOpenAIHTTPImageVariationRequestBase64JSON* UUnrealOpenAIHTTPImageVariationRequestBase64JSON::
CreateImageVariationJSON(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize)
{
	UUnrealOpenAIHTTPImageVariationRequestBase64JSON* ImageVariationRequest = NewObject<UUnrealOpenAIHTTPImageVariationRequestBase64JSON>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->Image = Image;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UUnrealOpenAIHTTPImageEditRequestURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");

		OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(Image, InvalidReason))
	{
		PrintDebugLogAndOnScreen(InvalidReason);

		OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(Mask, InvalidReason))
	{
		PrintDebugLogAndOnScreen(InvalidReason);

		OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	FCreateImageEditRequest RequestPayload;
	RequestPayload.image = Image;
	RequestPayload.mask = Mask;
	RequestPayload.response_format = "url";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.prompt = Prompt;
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  filename=\"image.png\"\r\n\r\n";

	const FString MaskBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"mask\";  filename=\"mask.png\"\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(Image);

	CombinedContent.Append(FStringToUInt8(MaskBoundary));
	CombinedContent.Append(Mask);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	CombinedContent.Append(FStringToUInt8(AddData("prompt", RequestPayload.prompt)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/edits", CombinedContent, EHTTPMethod::ECM_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseURL CreateImageVariationResponseURL;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseURL, 0, 0))
			{
				OnImageEditRequestCompleteURL.Broadcast(CreateImageVariationResponseURL, Response->GetContentAsString());
			}else
			{
				PrintDebugLogAndOnScreen("Failed to parse response to URL struct.");
				OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete image edit request");
			OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to process image edit request");
		OnImageEditRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
	});
}

UUnrealOpenAIHTTPImageEditRequestURL* UUnrealOpenAIHTTPImageEditRequestURL::CreateImageEditURL(
	UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize)
{
	UUnrealOpenAIHTTPImageEditRequestURL* ImageEditRequest = NewObject<UUnrealOpenAIHTTPImageEditRequestURL>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->Image = Image;
	ImageEditRequest->Mask = Mask;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}

void UUnrealOpenAIHTTPImageEditRequestBase64JSON::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");

		OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(Image, InvalidReason))
	{
		PrintDebugLogAndOnScreen(InvalidReason);

		OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(Mask, InvalidReason))
	{
		PrintDebugLogAndOnScreen(InvalidReason);

		OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	FCreateImageEditRequest RequestPayload;
	RequestPayload.image = Image;
	RequestPayload.mask = Mask;
	RequestPayload.response_format = "b64_json";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.prompt = Prompt;
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  filename=\"image.png\"\r\n\r\n";

	const FString MaskBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"mask\";  filename=\"mask.png\"\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(Image);

	CombinedContent.Append(FStringToUInt8(MaskBoundary));
	CombinedContent.Append(Mask);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	CombinedContent.Append(FStringToUInt8(AddData("prompt", RequestPayload.prompt)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/edits", CombinedContent, EHTTPMethod::ECM_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseBase64JSON CreateImageResponseBase64JSON;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageResponseBase64JSON, 0, 0))
			{
				OnImageEditRequestCompleteBase64JSON.Broadcast(CreateImageResponseBase64JSON, Response->GetContentAsString());
			}else
			{
				PrintDebugLogAndOnScreen("Failed to parse response to URL struct.");
				OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
			}
		}
		else
		{
			PrintDebugLogAndOnScreen("Failed to complete image edit request");
			OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to process image edit request");
		OnImageEditRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
	});
}

UUnrealOpenAIHTTPImageEditRequestBase64JSON* UUnrealOpenAIHTTPImageEditRequestBase64JSON::CreateImageEditJSON(
	UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize)
{
	UUnrealOpenAIHTTPImageEditRequestBase64JSON* ImageEditRequest = NewObject<UUnrealOpenAIHTTPImageEditRequestBase64JSON>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->Image = Image;
	ImageEditRequest->Mask = Mask;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}
