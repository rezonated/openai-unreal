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