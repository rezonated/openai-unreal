// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UnrealOpenAIConfig.generated.h"

/**
 * 
 */
UCLASS(Config = UnrealOpenAI, DefaultConfig)
class UNREALOPENAI_API UUnrealOpenAIConfig : public UObject
{
	GENERATED_BODY()

public:
	explicit UUnrealOpenAIConfig(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(Config, EditAnywhere, Category="Credentials")
	FString APIKey;

	UPROPERTY(Config, EditAnywhere, Category="Credentials")
	FString Organization;
};
