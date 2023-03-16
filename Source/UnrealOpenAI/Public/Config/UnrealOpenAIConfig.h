// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "UnrealOpenAIConfig.generated.h"

/**
 * Class used to hold the configuration .ini file for the UnrealOpenAI plugin
 * Consists of the API Key and Organization ID
 */
UCLASS(Config = Game, DefaultConfig)
class UNREALOPENAI_API UUnrealOpenAIConfig : public UObject
{
	GENERATED_BODY()

public:
	/**
	 *  Initialize the config object when created
	 * @param ObjectInitializer 
	 */
	explicit UUnrealOpenAIConfig(const FObjectInitializer& ObjectInitializer);

	/**
	 *  API Key for OpenAI API
	 */
	UPROPERTY(Config, EditAnywhere, Category="Credentials")
	FString APIKey;

	/**
	 *  Organization ID for OpenAI API
	 */
	UPROPERTY(Config, EditAnywhere, Category="Credentials")
	FString Organization;
};
