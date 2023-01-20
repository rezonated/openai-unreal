// Created, maintained by Vanan A. - rezonated @ github.com


#pragma once
#include "CoreMinimal.h"
#include "CommonDataTypes.h"
#include "FineTuneDataTypes.generated.h"

USTRUCT(BlueprintType)
struct FFineTuneEvent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune Event")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune Event")
	int32 created_at {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune Event")
	FString level;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune Event")
	FString message;
};

USTRUCT(BlueprintType)
struct FFineTune
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	int32 created_at {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	int32 updated_at {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString fine_tuned_model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString organization_id;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	FString status;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	TMap<FString, UObject*> hyperparams;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	TArray<FOpenAIFile> training_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	TArray<FOpenAIFile> validation_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	TArray<FOpenAIFile> result_files;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Fine Tune")
	TArray<FFineTuneEvent> events;
};

USTRUCT(BlueprintType)
struct FCreateFineTuneRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	FString training_file;
	
	TOptional<FString> validation_file;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	FString model;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	int n_epochs {4};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	int batch_size {0};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	float learning_rate_multiplier {1.0f};

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	float prompt_loss_weight {.01f};
	
	TOptional<bool> compute_classification_metrics = false;
	
	TOptional<int> classification_n_classes;
	
	TOptional<FString> classification_positive_class;
	
	TOptional<TArray<float>> classification_betas;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | Create Fine Tune Request")
	FString suffix;
};

USTRUCT(BlueprintType)
struct FListFineTunesResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | List Fine Tunes Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | List Fine Tunes Response")
	TArray<FFineTune> data;
};

USTRUCT(BlueprintType)
struct FListFineTuneEventsResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | List Fine Tune Events Response")
	FString object;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Open AI | List Fine Tune Events Response")
	TArray<FFineTuneEvent> data;
};
