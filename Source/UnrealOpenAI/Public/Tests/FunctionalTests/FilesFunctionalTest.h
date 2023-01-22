// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Tests/FunctionalTests/OpenAIFunctionalTestBase.h"
#include "FilesFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API AFilesFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()
public:
	AFilesFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Files")
	class AFunctionalTestPawn* TestPawn;

	UFUNCTION()
	void OnFileUploadTestComplete();

	UFUNCTION()
	void OnListFilesTestComplete(FString ID);

	UFUNCTION()
	void OnRetrieveFileTestComplete(FString ID);

	UFUNCTION()
	void OnDeleteFileTestComplete();
};
