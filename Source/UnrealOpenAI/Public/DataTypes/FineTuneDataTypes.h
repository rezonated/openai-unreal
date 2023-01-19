// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "FineTuneDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FFineTuneEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created_at;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString level;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString message;
};

USTRUCT(BlueprintType)
struct FFineTune
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 created_at;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int32 updated_at;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString fine_tuned_model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString organization_id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString status;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<FString, UObject*> hyperparams;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FOpenAIFile> training_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FOpenAIFile> validation_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FOpenAIFile> result_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FFineTuneEvent> events;
};

USTRUCT(BlueprintType)
struct FCreateFineTuneRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString training_file;
	
	TOptional<FString> validation_file;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int n_epochs = 4;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	int batch_size;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float learning_rate_multiplier;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	float prompt_loss_weight;
	
	TOptional<bool> compute_classification_metrics = false;
	
	TOptional<int> classification_n_classes;
	
	TOptional<FString> classification_positive_class;
	
	TOptional<TArray<float>> classification_betas;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString suffix;
};

USTRUCT(BlueprintType)
struct FListFineTunesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FFineTune> data;
};

USTRUCT(BlueprintType)
struct FListFineTuneEventsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TArray<FFineTuneEvent> data;
};
