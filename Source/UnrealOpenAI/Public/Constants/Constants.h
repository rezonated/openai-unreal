// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

#define OPENAI_FILE_SIZE_LIMIT 4194304

static const FString BaseURL = TEXT("https://api.openai.com/v1/");
static FString const BoundaryLabel = FString(TEXT("e543322540af456f9a3773049ca02529-")) + FString::FromInt(FMath::Rand());
static FString const BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
static FString BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

static const TArray<FString> HTTPMethods
{
	TEXT("GET"),
	TEXT("POST"),
	TEXT("PUT"),
	TEXT("DELETE"),
	TEXT("PATCH"),
	TEXT("HEAD"),
	TEXT("OPTIONS"),
	TEXT("TRACE"),
	TEXT("CONNECT")
};

static const TArray<FString> CompletionModels =
{
	"text-davinci-003",
	"text-curie-001",
	"text-babbage-001",
	"text-ada-001"
};

static const TArray<FString> ImageSizes =
{
	"256x256",
	"512x512",
	"1024x1024",
};