// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CompletionDataTypes.h"
#include "DataTypes/EditsDataTypes.h"
#include "DataTypes/EmbeddingsDataTypes.h"
#include "GameFramework/Pawn.h"
#include "FunctionalTestPawn.generated.h"

UCLASS()
class UNREALOPENAI_API AFunctionalTestPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AFunctionalTestPawn();

#pragma region Completion

	UPROPERTY()
	class ACreateCompletionFunctionalTest* CreateCompletionFunctionalTest;

	UFUNCTION()
	void StartCreateCompletionTest(FString Prompt);

	UFUNCTION()
	void OnCompletionSuccess(FCreateCompletionResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCompletionFailure(FCreateCompletionResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Edits

	UPROPERTY()
	class ACreateEditsFunctionalTest* CreateEditsFunctionalTest;
	
	UFUNCTION()
	void StartCreateEditsTest(FString Input, FString Instruction);

	UFUNCTION()
	void OnEditsSuccess(FCreateEditsResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnEditsFailure(FCreateEditsResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Embeddings

	UPROPERTY()
	class ACreateEmbeddingsFunctionalTest* CreateEmbeddingsFunctionalTest;

	UFUNCTION()
	void StartCreateEmbeddingsTest(FString Input);
	UFUNCTION()
	void OnEmbeddingsSuccess(FCreateEmbeddingsResponse Response, FString JSONString, FString Error);
	UFUNCTION()
	void OnEmbeddingsFailure(FCreateEmbeddingsResponse Response, FString JSONString, FString Error);


#pragma endregion 
	
};
