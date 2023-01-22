// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tests/FunctionalTests/OpenAIFunctionalTestBase.h"
#include "ImageURLFunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAITESTS_API AImageURLFunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()

public:
	AImageURLFunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Edits")
	class AFunctionalTestPawn* TestPawn;

	inline static const auto PluginTestDir = FString::Printf(TEXT("%sPlugins/UnrealOpenAI/Content/Test/"), *UKismetSystemLibrary::GetProjectDirectory());

	UFUNCTION()
	void OnCreateImageURLTestComplete();

	UFUNCTION()
	void OnCreateImageEditURLTestComplete();

	UFUNCTION()
	void OnCreateImageEditVariationURLTestComplete();
};
