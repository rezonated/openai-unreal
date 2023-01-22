// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CompletionDataTypes.h"
#include "DataTypes/EditsDataTypes.h"
#include "DataTypes/EmbeddingsDataTypes.h"
#include "DataTypes/FilesDataTypes.h"
#include "DataTypes/ImageDataTypes.h"
#include "DataTypes/ModerationDataTypes.h"
#include "GameFramework/Pawn.h"
#include "Tests/FunctionalTests/FilesFunctionalTest.h"
#include "Tests/FunctionalTests/ImageBase64FunctionalTest.h"
#include "Tests/FunctionalTests/ImageURLFunctionalTest.h"
#include "Tests/FunctionalTests/ModerationsFunctionalTest.h"
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
	class ACompletionsFunctionalTest* CompletionsFunctionalTest;

	UFUNCTION()
	void StartCompletionsTest(FString Prompt);

	UFUNCTION()
	void OnCompletionSuccess(FCreateCompletionResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCompletionFailure(FCreateCompletionResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Edits

	UPROPERTY()
	class AEditsFunctionalTest* EditsFunctionalTest;
	
	UFUNCTION()
	void StartEditsTest(FString Input, FString Instruction);

	UFUNCTION()
	void OnEditsSuccess(FCreateEditsResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnEditsFailure(FCreateEditsResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Embeddings

	UPROPERTY()
	class AEmbeddingsFunctionalTest* EmbeddingsFunctionalTest;

	UFUNCTION()
	void StartEmbeddingsTest(FString Input);
	UFUNCTION()
	void OnEmbeddingsSuccess(FCreateEmbeddingsResponse Response, FString JSONString, FString Error);
	UFUNCTION()
	void OnEmbeddingsFailure(FCreateEmbeddingsResponse Response, FString JSONString, FString Error);


#pragma endregion

#pragma region Moderation

	UPROPERTY()
	AModerationsFunctionalTest* ModerationsFunctionalTest;
	
	UFUNCTION()
	void StartModerationsTest(FString Input);

	UFUNCTION()
	void OnModerationSuccess(FCreateModerationResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnModerationFailure(FCreateModerationResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Files

	UPROPERTY()
	AFilesFunctionalTest* FilesFunctionalTest;
	
	UFUNCTION()
	void StartCreateFileTest(const FString TestFilePath);

	UFUNCTION()
	void OnCreateFileSuccess(FFileResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateFileFailure(FFileResponse Response, FString JSONString, FString Error);
	
	UFUNCTION()
	void StartListFilesTest();

	UFUNCTION()
	void OnListFileSuccess(FListFilesResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnListFileFailure(FListFilesResponse Response, FString JSONString, FString Error);
	
	UFUNCTION()
	void StartRetrieveFileTest(FString ID);

	FString FileID;

	UFUNCTION()
	void OnRetrieveFileSuccess(FFileResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnRetrieveFileFailure(FFileResponse Response, FString JSONString, FString Error);
	
	UFUNCTION()
	void StartDeleteFileTest(FString ID);

	UFUNCTION()
	void OnDeleteFileSuccess(FDeleteResponse Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnDeleteFileFailure(FDeleteResponse Response, FString JSONString, FString Error);

#pragma endregion

#pragma region Image URL

	UPROPERTY()
	AImageURLFunctionalTest* ImageURLFunctionalTest;
	
	UFUNCTION()
	void StartCreateImageURLTest(FString Prompt);
	
	UFUNCTION()
	void OnCreateImageURLSuccess(FCreateImageResponseURL Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageURLFailure(FCreateImageResponseURL Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnGetCreateImageFromURLSuccess(UTexture2D* Texture2D);

	UFUNCTION()
	void OnGetCreateImageFromURLFailure(UTexture2D* Texture2D);
	
	UFUNCTION()
	void StartCreateImageEditURLTest(FString ImagePath, FString MaskPath, FString Prompt);
	
	UFUNCTION()
	void OnCreateImageEditURLSuccess(FCreateImageResponseURL ResponseURL, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageEditURLFailure(FCreateImageResponseURL ResponseURL, FString JSONString, FString Error);

	UFUNCTION()
	void OnGetCreateImageEditFromURLSuccess(UTexture2D* Texture2D);

	UFUNCTION()
	void OnGetCreateImageEditFromURLFailure(UTexture2D* Texture2D);
	
	UFUNCTION()
	void StartCreateImageEditVariationURLTest(FString ImagePath);
	
	UFUNCTION()
	void OnCreateImageEditVariationURLSuccess(FCreateImageResponseURL ResponseURL, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageEditVariationURLFailure(FCreateImageResponseURL ResponseURL, FString JSONString, FString Error);

	UFUNCTION()
	void OnGetCreateImageEditVariationFromURLSuccess(UTexture2D* Texture2D);

	UFUNCTION()
	void OnGetCreateImageEditVariationFromURLFailure(UTexture2D* Texture2D);

#pragma endregion

#pragma region Image Base64

	UPROPERTY()
	AImageBase64FunctionalTest* ImageBase64FunctionalTest;
	
	UFUNCTION()
	void StartCreateImageBase64Test(FString Prompt);

	UFUNCTION()
	void OnCreateImageBase64Success(FCreateImageResponseBase64JSON Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageBase64Failure(FCreateImageResponseBase64JSON Response, FString JSONString, FString Error);
	
	UFUNCTION()
	void StartCreateImageEditBase64Test(FString ImagePath, FString MaskPath, const FString Prompt);

	UFUNCTION()
	void OnCreateImageEditBase64Success(FCreateImageResponseBase64JSON Response, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageEditBase64Failure(FCreateImageResponseBase64JSON ResponseBase64JSON, FString JSONString, FString Error);
	
	UFUNCTION()
	void StartCreateImageEditVariationBase64Test(FString ImagePath);

	UFUNCTION()
	void OnCreateImageEditVariationBase64Success(FCreateImageResponseBase64JSON ResponseBase64JSON, FString JSONString, FString Error);

	UFUNCTION()
	void OnCreateImageEditVariationBase64Failure(FCreateImageResponseBase64JSON ResponseBase64JSON, FString JSONString, FString Error);

#pragma endregion 
};
