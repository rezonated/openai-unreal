// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "Constants/ImageConstants.h"
#include "Enums/ImageEnums.h"
#include "ImageDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FCreateImageRequestBase
{
	GENERATED_BODY()
	
	TOptional<int> n = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Request Base")
	FString size = ImageSizes[static_cast<int>(EImageSize::EIS_1024)];

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Request Base")
	FString response_format = "b64_json";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Request Base")
	FString user;
};

USTRUCT(BlueprintType)
struct FCreateImageRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Request")
	FString prompt;
};

USTRUCT(BlueprintType)
struct FCreateImageEditRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Edit Request")
	TArray<uint8> image;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Edit Request")
	TArray<uint8> mask;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Edit Request")
	FString prompt;
};

USTRUCT(BlueprintType)
struct FCreateImageVariationRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Variation Request")
	TArray<uint8> image;
};

USTRUCT(BlueprintType)
struct FImageDataURL
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Image Data URL")
	FString url;
};

USTRUCT(BlueprintType)
struct FImageDataBase64JSON
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Image Data Base64 JSON")
	FString b64_json;
};

USTRUCT(BlueprintType)
struct FCreateImageResponseURL
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Response URL")
	int32 created {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Response URL")
	TArray<FImageDataURL> data;
};

USTRUCT(BlueprintType)
struct FCreateImageResponseBase64JSON
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Response Base64 JSON")
	int32 created {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Image Response Base64 JSON")
	TArray<FImageDataBase64JSON> data;	
};
