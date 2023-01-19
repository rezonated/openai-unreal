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

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString size = ImageSizes[static_cast<int>(EImageSize::EIS_1024)];

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString response_format = "b64_json";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString user;
};

USTRUCT(BlueprintType)
struct FCreateImageRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt;
};

USTRUCT(BlueprintType)
struct FCreateImageEditRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<uint8> image;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<uint8> mask;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt;
};

USTRUCT(BlueprintType)
struct FCreateImageVariationRequest : public FCreateImageRequestBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<uint8> image;
};

USTRUCT(BlueprintType)
struct FImageDataURL
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString url;
};

USTRUCT(BlueprintType)
struct FImageDataBase64JSON
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString b64_json;
};

USTRUCT(BlueprintType)
struct FCreateImageResponseURL
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FImageDataURL> data;
};

USTRUCT(BlueprintType)
struct FCreateImageResponseBase64JSON
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FImageDataBase64JSON> data;	
};
