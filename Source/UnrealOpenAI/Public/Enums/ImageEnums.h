// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "ImageEnums.generated.h"

UENUM(BlueprintType)
enum class EImageSize : uint8
{
	EIS_256 UMETA(DisplayName = "256x256"),
	EIS_512 UMETA(DisplayName = "512x512"),
	EIS_1024 UMETA(DisplayName = "1024x1024"),
	
	EIS_MAX UMETA(Hidden)
};
