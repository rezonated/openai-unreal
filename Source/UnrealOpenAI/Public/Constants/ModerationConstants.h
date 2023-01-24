// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

/**
 *  Constants for Moderations API
 */

/**
 * Default models to use for moderation, as defined by OpenAI:
 * https://beta.openai.com/docs/api-reference/moderations/create#moderations/create-model
 */
static const TArray<FString> ModerationModels =
{
	"text-moderation-stable",
	"text-moderation-latest",
};