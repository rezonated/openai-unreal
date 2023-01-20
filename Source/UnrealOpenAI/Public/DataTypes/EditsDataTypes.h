// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "EditsDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FCreateEditsRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Request")
	FString model = "text-davinci-edit-001";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Request")
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Request")
	FString instruction;
	
	TOptional<float> temperature = 0.f;
	
	TOptional<float> top_p = 1.f;
	
	TOptional<int> n = 1;
};


USTRUCT(BlueprintType)
struct FCreateEditsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Response")
	int32 created {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Response")
	TArray<FChoice> choices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category="Open AI | Create Edits Response")
	FUsage usage;
	
};
