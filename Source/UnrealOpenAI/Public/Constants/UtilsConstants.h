// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

/**
 *  Constants for Utils for the wrapper.
 */

/**
 * OpenAI file size limit in bytes, as defined by OpenAI:
 * https://beta.openai.com/docs/api-reference/images/create-edit#images/create-edit-image
 */
#define OPENAI_FILE_SIZE_LIMIT 4194304

/**
 * Base URL for OpenAI's API
 */
static const FString BaseURL = TEXT("https://api.openai.com/v1/");

/**
 * Boundary labels for multipart/form-data requests, randomly generated
 */
static FString const BoundaryLabel = FString(TEXT("e543322540af456f9a3773049ca02529-")) + FString::FromInt(FMath::Rand());
static FString const BoundaryBegin = FString(TEXT("--")) + BoundaryLabel + FString(TEXT("\r\n"));
static FString BoundaryEnd = FString(TEXT("\r\n--")) + BoundaryLabel + FString(TEXT("--\r\n"));

/**
 * HTTP methods for sending requests, as defined in:
 * https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
 */
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