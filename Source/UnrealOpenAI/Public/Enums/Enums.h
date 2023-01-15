// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class ECompletionModel : uint8
{
	ECM_Davinci UMETA(DisplayName = "Davinci"),
	ECM_Curie UMETA(DisplayName = "Curie"),
	ECM_Babbage UMETA(DisplayName = "Babbage"),
	ECM_Ada UMETA(DisplayName = "Ada"),

	ECM_MAX UMETA(Hidden)
};

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

UENUM(BlueprintType)
enum class EImageSize : uint8
{
	EIS_256 UMETA(DisplayName = "256x256"),
	EIS_512 UMETA(DisplayName = "512x512"),
	EIS_1024 UMETA(DisplayName = "1024x1024"),
	
	EIS_MAX UMETA(Hidden)
};
