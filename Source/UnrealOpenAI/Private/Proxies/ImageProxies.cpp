// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/ImageProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Image Proxies

UCreateImageRequestURL* UCreateImageRequestURL::CreateImageURL(UObject* WorldContextObject,
	FString Prompt, EImageSize ImageSize)
{
	UCreateImageRequestURL* ImageRequestURL = NewObject<UCreateImageRequestURL>();
	ImageRequestURL->WorldContextObject = WorldContextObject;
	ImageRequestURL->Prompt = Prompt;
	ImageRequestURL->ImageSize = ImageSize;
	return ImageRequestURL;
}

void UCreateImageRequestURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	if (Prompt.IsEmpty())
	{
		PrintDebugLogAndOnScreen("Prompt is empty");
		OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		PrintDebugLogAndOnScreen("Image size is invalid");
		OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
		return;
	}

	FCreateImageRequest RequestPayload;
	RequestPayload.prompt = Prompt;
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.response_format = TEXT("url");
		
	FString JSONPayload;
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("images/generations"), JSONPayload, EHTTPMethod::ECM_POST,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);
				
				FCreateImageResponseURL ImageResponse;
				
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ImageResponse, 0, 0))
				{
					OnImageRequestCompleteURL.Broadcast(ImageResponse, Response->GetContentAsString());
				}
				else
				{
					PrintDebugLogAndOnScreen("Failed to convert image JSON response to struct");
					OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
				}
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to complete image request");
				OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
			}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete image request");OnImageRequestFailedURL.Broadcast(FCreateImageResponseURL(), TEXT(""));
	});
}


UCreateImageRequestBase64JSON* UCreateImageRequestBase64JSON::CreateImageBase64JSON(
	UObject* WorldContextObject, FString Prompt, EImageSize ImageSize)
{
	UCreateImageRequestBase64JSON* ImageRequestBase64JSON = NewObject<UCreateImageRequestBase64JSON>();
	ImageRequestBase64JSON->WorldContextObject = WorldContextObject;
	ImageRequestBase64JSON->Prompt = Prompt;
	ImageRequestBase64JSON->ImageSize = ImageSize;
	return ImageRequestBase64JSON;
}

void UCreateImageRequestBase64JSON::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	if (Prompt.IsEmpty())
	{
		PrintDebugLogAndOnScreen("Prompt is empty");
		OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		PrintDebugLogAndOnScreen("Image size is invalid");
		OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
		return;
	}

	FCreateImageRequest RequestPayload;
	RequestPayload.prompt = Prompt;
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.response_format = TEXT("b64_json");
		
	FString JSONPayload;
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("images/generations"), JSONPayload, EHTTPMethod::ECM_POST,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);
				
				FCreateImageResponseBase64JSON ImageResponse;
				
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ImageResponse, 0, 0))
				{
					OnImageRequestCompleteBase64JSON.Broadcast(ImageResponse, Response->GetContentAsString());
				}
				else
				{
					PrintDebugLogAndOnScreen("Failed to convert image JSON response to struct");
					OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
				}
			}
			else
			{
				PrintDebugLogAndOnScreen("Failed to complete image request");
				OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
			}
	}, [this]
	{
		PrintDebugLogAndOnScreen("Failed to complete image request");OnImageRequestFailedBase64JSON.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""));
	});
}

#pragma endregion

#pragma region Create Image Edit Proxies

UCreateImageEditRequestURL* UCreateImageEditRequestURL::CreateImageEditURL(
	UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize)
{
	UCreateImageEditRequestURL* ImageEditRequest = NewObject<UCreateImageEditRequestURL>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->Image = Image;
	ImageEditRequest->Mask = Mask;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}

void UCreateImageEditRequestURL::Activate()
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

UCreateImageEditRequestBase64JSON* UCreateImageEditRequestBase64JSON::CreateImageEditJSON(
	UObject* WorldContextObject, TArray<uint8> Image, TArray<uint8> Mask, FString Prompt, EImageSize ImageSize)
{
	UCreateImageEditRequestBase64JSON* ImageEditRequest = NewObject<UCreateImageEditRequestBase64JSON>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->Image = Image;
	ImageEditRequest->Mask = Mask;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}

void UCreateImageEditRequestBase64JSON::Activate()
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

#pragma endregion

#pragma region Create Image Variation Proxies

UCreateImageVariationRequestURL* UCreateImageVariationRequestURL::CreateImageVariationURL(
	UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize)
{
	UCreateImageVariationRequestURL* ImageVariationRequest = NewObject<UCreateImageVariationRequestURL>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->Image = Image;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UCreateImageVariationRequestURL::Activate()
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

UCreateImageVariationRequestBase64JSON* UCreateImageVariationRequestBase64JSON::
CreateImageVariationJSON(UObject* WorldContextObject, TArray<uint8> Image, EImageSize ImageSize)
{
	UCreateImageVariationRequestBase64JSON* ImageVariationRequest = NewObject<UCreateImageVariationRequestBase64JSON>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->Image = Image;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UCreateImageVariationRequestBase64JSON::Activate()
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

#pragma endregion