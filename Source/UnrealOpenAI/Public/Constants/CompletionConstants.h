// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

/**
 *  Constants for the Completion API
 */

// Default models to use for completion, as defined by OpenAI:
// https://beta.openai.com/docs/models/gpt-3
static const TArray<FString> CompletionModels =
{
	"text-davinci-003",
	"text-curie-001",
	"text-babbage-001",
	"text-ada-001"
};