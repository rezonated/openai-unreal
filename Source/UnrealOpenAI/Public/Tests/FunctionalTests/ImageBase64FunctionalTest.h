// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tests/FunctionalTests/OpenAIFunctionalTestBase.h"
#include "ImageBase64FunctionalTest.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API AImageBase64FunctionalTest : public AOpenAIFunctionalTestBase
{
	GENERATED_BODY()

public:
	AImageBase64FunctionalTest();

	virtual void OnTestStartHandler() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Open AI - Edits")
	class AFunctionalTestPawn* TestPawn;

	inline static const auto PluginTestDir = FString::Printf(TEXT("%sPlugins/UnrealOpenAI/Content/Test/"), *UKismetSystemLibrary::GetProjectDirectory());

	UFUNCTION()
	void OnCreateImageBase64TestComplete();

	UFUNCTION()
	void OnCreateImageEditBase64TestComplete();

	UFUNCTION()
	void OnCreateImageEditVariationBase64TestComplete();
};
