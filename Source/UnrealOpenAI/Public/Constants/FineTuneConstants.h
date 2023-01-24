// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

/**
 *  Constants for the FineTune API
 */

// Default models to use for fine-tuning, as defined by OpenAI:
// https://beta.openai.com/docs/api-reference/fine-tunes/create#fine-tunes/create-model
static const TArray<FString> FineTuneModels =
{
	"ada",
	"babbage",
	"curie",
	"davinci"
};