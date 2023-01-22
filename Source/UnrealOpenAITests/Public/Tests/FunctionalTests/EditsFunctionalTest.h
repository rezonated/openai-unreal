// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "OpenAIFunctionalTestBase.h"
#include "UObject/Object.h"
#include "EditsFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAITESTS_API AEditsFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()

public:
	AEditsFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Edits")
	class AFunctionalTestPawn* TestPawn;
};
