// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "ModerationEnums.generated.h"

UENUM(BlueprintType)
enum class EModerationModels : uint8
{
	EMM_Stable UMETA(DisplayName = "Stable"),
	EMM_Latest UMETA(DisplayName = "Latest"),

	EMM_MAX UMETA(Hidden)
};
