// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "UtilsEnums.generated.h"

// Enums for available HTTP methods, defined in:
// https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods
UENUM(BlueprintType)
enum class EHTTPMethod : uint8
{
	EHP_GET UMETA(DisplayName = "GET"),
	EHP_POST UMETA(DisplayName = "POST"),
	EHP_PUT UMETA(DisplayName = "PUT"),
	EHP_DELETE UMETA(DisplayName = "DELETE"),
	EHP_PATCH UMETA(DisplayName = "PATCH"),
	EHP_HEAD UMETA(DisplayName = "HEAD"),
	EHP_OPTIONS UMETA(DisplayName = "OPTIONS"),
	EHP_TRACE UMETA(DisplayName = "TRACE"),
	EHP_CONNECT UMETA(DisplayName = "CONNECT"),
	
	EHP_MAX UMETA(Hidden)
};
