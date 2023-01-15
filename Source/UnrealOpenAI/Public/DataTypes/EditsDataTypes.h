// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "EditsDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FCreateEditsRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model = "text-davinci-edit-001";

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString input;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString instruction;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float temperature = 0.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float top_p = 1.f;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int n = 1;
};


USTRUCT(BlueprintType)
struct FCreateEditsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FChoice choices;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FUsage usage;
	
};
