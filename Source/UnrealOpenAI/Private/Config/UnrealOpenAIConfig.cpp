// Created, maintained by Vanan A. - rezonated @ github.com


#include "Config/UnrealOpenAIConfig.h"

UUnrealOpenAIConfig::UUnrealOpenAIConfig(const FObjectInitializer& ObjectInitializer)
{
	// By default, the API Key and Organization ID are empty
	APIKey = TEXT("");
	Organization = TEXT("");
}
