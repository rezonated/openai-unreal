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
	ECM_GET UMETA(DisplayName = "GET"),
	ECM_POST UMETA(DisplayName = "POST"),
	ECM_PUT UMETA(DisplayName = "PUT"),
	ECM_DELETE UMETA(DisplayName = "DELETE"),
	ECM_PATCH UMETA(DisplayName = "PATCH"),
	ECM_HEAD UMETA(DisplayName = "HEAD"),
	ECM_OPTIONS UMETA(DisplayName = "OPTIONS"),
	ECM_TRACE UMETA(DisplayName = "TRACE"),
	ECM_CONNECT UMETA(DisplayName = "CONNECT"),
	
	ECM_MAX UMETA(Hidden)
};

UENUM(BlueprintType)
enum class EImageSize : uint8
{
	EIS_256 UMETA(DisplayName = "256x256"),
	EIS_512 UMETA(DisplayName = "512x512"),
	EIS_1024 UMETA(DisplayName = "1024x1024"),
	
	EIS_MAX UMETA(Hidden)
};
