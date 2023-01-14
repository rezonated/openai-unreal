// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealOpenAIUtils.generated.h"
/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtils : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	static TArray<uint8> OpenFileDialog();
};
