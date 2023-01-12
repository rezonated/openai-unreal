#pragma once
#include "UnrealOpenAI.h"

static const FString BaseURL = TEXT("https://api.openai.com/v1/");

static void PrintDebugOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, Message);
	}
}

static void PrintDebugLog(const FString& Message)
{
	UE_LOG(LogTypeOpenAI, Warning, TEXT("%s"), *Message);
}

static void PrintDebugLogAndOnScreen(const FString& Message, const float Duration = 2.f, const FColor& Color = FColor::White)
{
	PrintDebugLog(Message);
	PrintDebugOnScreen(Message, Duration, Color);
}