// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "OpenAIFunctionalTestBase.h"
#include "GameFramework/Actor.h"
#include "EmbeddingsFunctionalTest.generated.h"

UCLASS()
class UNREALOPENAI_API AEmbeddingsFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()

public:
	AEmbeddingsFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Edits")
	class AFunctionalTestPawn* TestPawn;
};
