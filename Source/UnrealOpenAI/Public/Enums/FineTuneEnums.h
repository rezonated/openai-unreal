﻿// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "FineTuneEnums.generated.h"

// Enums for available fine-tune models, defined in:
// https://beta.openai.com/docs/api-reference/fine-tunes/create#fine-tunes/create-model
UENUM(BlueprintType)
enum class EFineTuneModels : uint8
{
	EFTM_Ada 	UMETA(DisplayName = "Ada"),
	EFTM_Babbage 	UMETA(DisplayName = "Babbage"),
	EFTM_Curie 	UMETA(DisplayName = "Curie"),
	EFTM_Davinci 	UMETA(DisplayName = "Davinci"),
	
	EFTM_MAX UMETA(Hidden)
};
