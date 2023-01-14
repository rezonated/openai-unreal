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