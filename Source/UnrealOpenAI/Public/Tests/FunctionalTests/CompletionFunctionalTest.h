// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "OpenAIFunctionalTestBase.h"
#include "CompletionFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API ACreateCompletionFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()

public:

	ACreateCompletionFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Completion")
	class AFunctionalTestPawn* TestPawn;
};
