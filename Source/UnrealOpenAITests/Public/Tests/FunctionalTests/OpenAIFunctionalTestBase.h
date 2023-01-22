// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "FunctionalTest.h"
#include "OpenAIFunctionalTestBase.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAITESTS_API AOpenAIFunctionalTestBase : public AFunctionalTest
{
	GENERATED_BODY()

public:
	AOpenAIFunctionalTestBase();

	UFUNCTION()
	void OnTestPrepareHandler();
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnTestStartHandler();

	virtual void PrepareTest() override;

	virtual bool IsReady_Implementation() override;

	virtual void StartTest() override;

	virtual void FinishTest(EFunctionalTestResult TestResult, const FString& Message) override;

	UFUNCTION()
	virtual void FailTest(FString Message);

	UFUNCTION()
	virtual void PassTest(FString Message);
	
};
