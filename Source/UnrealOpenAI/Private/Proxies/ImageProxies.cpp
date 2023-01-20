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
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Prompt.IsEmpty())
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}

	FCreateImageRequest RequestPayload;
	RequestPayload.prompt = Prompt;
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.response_format = TEXT("url");
		
	FString JSONPayload;
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("images/generations"), JSONPayload, EHTTPMethod::EHP_POST,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					OnFailure.Broadcast(FCreateImageResponseURL(), ResponseString, ErrorMessage);
					return;
				}
				
				FCreateImageResponseURL ImageResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ImageResponse, 0, 0))
				{
					OnSuccess.Broadcast(ImageResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to convert create image URL response to struct"));
				}
			}
			else
			{
				OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Create image URL request failed"));
			}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to send create image URL request"));
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
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Prompt.IsEmpty())
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}

	FCreateImageRequest RequestPayload;
	RequestPayload.prompt = Prompt;
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.response_format = TEXT("b64_json");
		
	FString JSONPayload;
	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("images/generations"), JSONPayload, EHTTPMethod::EHP_POST,
		[this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful){
			if (bWasSuccessful)
			{
				FString ResponseString = Response->GetContentAsString();
				ResponseString = SanitizeString(ResponseString);

				if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
				{
					OnFailure.Broadcast(FCreateImageResponseBase64JSON(), ResponseString, ErrorMessage);
					return;
				}
				
				FCreateImageResponseBase64JSON ImageResponse;
				if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &ImageResponse, 0, 0))
				{
					OnSuccess.Broadcast(ImageResponse, Response->GetContentAsString(), TEXT(""));
				}
				else
				{
					OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to convert create image JSON response to struct"));
				}
			}
			else
			{
				OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Send create image JSON request failed"));
			}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to send create image JSON request"));
	});
}

#pragma endregion

#pragma region Create Image Edit Proxies

UCreateImageEditRequestURL* UCreateImageEditRequestURL::CreateImageEditURL(UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize)
{
	UCreateImageEditRequestURL* ImageEditRequest = NewObject<UCreateImageEditRequestURL>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->ImageFile = ImageFile;
	ImageEditRequest->MaskImageFile = MaskImageFile;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}

void UCreateImageEditRequestURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(ImageFile.FileData, InvalidReason))
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), InvalidReason);
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(MaskImageFile.FileData, InvalidReason))
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), InvalidReason);
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}

	if (Prompt.IsEmpty() || Prompt.Len() <= 0 || Prompt == TEXT(""))
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}
	

	FCreateImageEditRequest RequestPayload;
	RequestPayload.image = ImageFile.FileData;
	RequestPayload.mask = MaskImageFile.FileData;
	RequestPayload.response_format = "url";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.prompt = Prompt;
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  " + FString::Printf(TEXT("filename=\"%s\""), *ImageFile.FileName) + "\r\n\r\n";

	const FString MaskBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"mask\";  " + FString::Printf(TEXT("filename=\"%s\""), *MaskImageFile.FileName) + "\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(ImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(MaskBoundary));
	CombinedContent.Append(MaskImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	CombinedContent.Append(FStringToUInt8(AddData("prompt", RequestPayload.prompt)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/edits", CombinedContent, EHTTPMethod::EHP_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseURL CreateImageVariationResponseURL;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseURL, 0, 0))
			{
				OnSuccess.Broadcast(CreateImageVariationResponseURL, Response->GetContentAsString(), TEXT(""));
			}else
			{
				OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to to convert create edit image URL response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Create image edit URL request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to send create image edit URL request"));
	});
}

UCreateImageEditRequestBase64JSON* UCreateImageEditRequestBase64JSON::CreateImageEditJSON(
	UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize)
{
	UCreateImageEditRequestBase64JSON* ImageEditRequest = NewObject<UCreateImageEditRequestBase64JSON>();
	ImageEditRequest->WorldContextObject = WorldContextObject;
	ImageEditRequest->ImageFile = ImageFile;
	ImageEditRequest->MaskImageFile = MaskImageFile;
	ImageEditRequest->Prompt = Prompt;
	ImageEditRequest->ImageSize = ImageSize;
	return ImageEditRequest;
}

void UCreateImageEditRequestBase64JSON::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(ImageFile.FileData, InvalidReason))
	{
		
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), InvalidReason);
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(MaskImageFile.FileData, InvalidReason))
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), InvalidReason);
		return;
	}

	if (Prompt.IsEmpty() || Prompt.Len() <= 0 || Prompt == TEXT(""))
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Prompt is empty"));
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}

	FCreateImageEditRequest RequestPayload;
	RequestPayload.image = ImageFile.FileData;
	RequestPayload.mask = MaskImageFile.FileData;
	RequestPayload.response_format = "b64_json";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	RequestPayload.prompt = Prompt;
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  " + FString::Printf(TEXT("filename=\"%s\""), *ImageFile.FileName) + "\r\n\r\n";

	const FString MaskBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"mask\";  " + FString::Printf(TEXT("filename=\"%s\""), *MaskImageFile.FileName) + "\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(ImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(MaskBoundary));
	CombinedContent.Append(MaskImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	CombinedContent.Append(FStringToUInt8(AddData("prompt", RequestPayload.prompt)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/edits", CombinedContent, EHTTPMethod::EHP_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FCreateImageResponseBase64JSON(), ResponseString, ErrorMessage);
				return;
			}

			FCreateImageResponseBase64JSON CreateImageResponseBase64JSON;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageResponseBase64JSON, 0, 0))
			{
				OnSuccess.Broadcast(CreateImageResponseBase64JSON, Response->GetContentAsString(), TEXT(""));
			}else
			{
				OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to convert create edit image JSON response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Create image edit JSON request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to send create image edit JSON request"));
	});
}

#pragma endregion

#pragma region Create Image Variation Proxies

UCreateImageVariationRequestURL* UCreateImageVariationRequestURL::CreateImageVariationURL(
	UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize)
{
	UCreateImageVariationRequestURL* ImageVariationRequest = NewObject<UCreateImageVariationRequestURL>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->ImageFile = ImageFile;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UCreateImageVariationRequestURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (FString InvalidReason; !ValidateImageForOpenAI(ImageFile.FileData, InvalidReason))
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), InvalidReason);
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}

	FCreateImageVariationRequest RequestPayload;
	RequestPayload.image = ImageFile.FileData;
	RequestPayload.response_format = "url";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  " + FString::Printf(TEXT("filename=\"%s\""), *ImageFile.FileName) + "\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(ImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/variations", CombinedContent, EHTTPMethod::EHP_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseURL CreateImageVariationResponseURL;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseURL, 0, 0))
			{
				OnSuccess.Broadcast(CreateImageVariationResponseURL, Response->GetContentAsString(), TEXT(""));
			}else
			{
				OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to convert create image variation URL response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Create image variation URL request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseURL(), TEXT(""), TEXT("Failed to send create image variation URL request"));
	});
}

UCreateImageVariationRequestBase64JSON* UCreateImageVariationRequestBase64JSON::
CreateImageVariationJSON(UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize)
{
	UCreateImageVariationRequestBase64JSON* ImageVariationRequest = NewObject<UCreateImageVariationRequestBase64JSON>();
	ImageVariationRequest->WorldContextObject = WorldContextObject;
	ImageVariationRequest->ImageFile = ImageFile;
	ImageVariationRequest->ImageSize = ImageSize;
	return ImageVariationRequest;
}

void UCreateImageVariationRequestBase64JSON::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if(FString ReasonInvalid; !ValidateImageForOpenAI(ImageFile.FileData, ReasonInvalid))
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), ReasonInvalid);
		return;
	}

	if (ImageSize == EImageSize::EIS_MAX)
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Image size is invalid"));
		return;
	}
	
	FCreateImageVariationRequest RequestPayload;
	RequestPayload.image = ImageFile.FileData;
	RequestPayload.response_format = "b64_json";
	RequestPayload.size = ImageSizes[static_cast<int>(ImageSize)];
	
	TArray<uint8> CombinedContent;

	const FString ImageBoundary = FString(TEXT("\r\n")) + BoundaryBegin + "Content-Disposition: form-data; name=\"image\";  " + FString::Printf(TEXT("filename=\"%s\""), *ImageFile.FileName) + "\r\n\r\n";
	
	CombinedContent.Append(FStringToUInt8(ImageBoundary));
	CombinedContent.Append(ImageFile.FileData);

	CombinedContent.Append(FStringToUInt8(AddData("response_format", RequestPayload.response_format)));
	CombinedContent.Append(FStringToUInt8(AddData("size", RequestPayload.size)));
	
	CombinedContent.Append(FStringToUInt8(BoundaryEnd));

	SendPayloadMultipartFormData("images/variations", CombinedContent, EHTTPMethod::EHP_POST, [this] (FHttpRequestPtr Request, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if(bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			FCreateImageResponseBase64JSON CreateImageVariationResponseBase64JSON;

			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &CreateImageVariationResponseBase64JSON, 0, 0))
			{
				OnSuccess.Broadcast(CreateImageVariationResponseBase64JSON, Response->GetContentAsString(), TEXT(""));
			}else
			{
				OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to convert create image variation JSON response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Create image variation JSON request failed"));
		}
	}, [this]
	{
		OnFailure.Broadcast(FCreateImageResponseBase64JSON(), TEXT(""), TEXT("Failed to send create image variation JSON request"));
	});
}

#pragma endregion