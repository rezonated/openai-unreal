// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CompletionEnums.generated.h"

// Enums for available completion models, defined in:
// https://beta.openai.com/docs/models/gpt-3
UENUM(BlueprintType)
enum class ECompletionModel : uint8
{
	ECM_Davinci UMETA(DisplayName = "Davinci"),
	ECM_Curie UMETA(DisplayName = "Curie"),
	ECM_Babbage UMETA(DisplayName = "Babbage"),
	ECM_Ada UMETA(DisplayName = "Ada"),

	ECM_MAX UMETA(Hidden)
};
