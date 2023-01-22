// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "OpenAIFunctionalTestBase.h"
#include "ModerationsFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAITESTS_API AModerationsFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()
public:
	AModerationsFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Moderation")
	class AFunctionalTestPawn* TestPawn;
};
