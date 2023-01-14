#pragma once
#include "CoreMinimal.h"
#include "Constants/Constants.h"
#include "Enums/Enums.h"
#include "DataTypes.generated.h"

USTRUCT(BlueprintType)
struct FChoice
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString text;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int index;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString finish_reason;
};

USTRUCT(BlueprintType)
struct FUsage
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString completion_tokens;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString total_tokens;
};

USTRUCT(BlueprintType)
struct FCreateCompletionRequest
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString prompt = "<|endoftext|>";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString suffix;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int max_tokens = 1000;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float temperature = 0;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float top_p = 1.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int n = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool stream = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int logprobs = 5;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	bool echo = false;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString stop;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float presence_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float frequency_penalty = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int best_of = 1;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, FString> logit_bias;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString user;
};

USTRUCT(BlueprintType)
struct FCreateCompletionResponse
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FChoice choices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUsage usage;
};

USTRUCT(BlueprintType)
struct FCreateImageRequestBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	uint8 n = 1;

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
