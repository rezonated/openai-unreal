// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once

/**
 *  Constants for the Image API
 */

// Image sizes accepted by OpenAI's Image API:
// https://beta.openai.com/docs/api-reference/images/create#images/create-size
static const TArray<FString> ImageSizes =
{
	"256x256",
	"512x512",
	"1024x1024",
};