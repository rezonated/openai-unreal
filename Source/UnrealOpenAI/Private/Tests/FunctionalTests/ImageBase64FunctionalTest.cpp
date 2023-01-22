// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/ImageBase64FunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

AImageBase64FunctionalTest::AImageBase64FunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AImageBase64FunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->ImageBase64FunctionalTest = this;

	TestPawn->StartCreateImageBase64Test(TEXT("A cute baby sea otter"));
}

void AImageBase64FunctionalTest::OnCreateImageBase64TestComplete()
{
	TestPawn->StartCreateImageEditBase64Test(FString::Printf(TEXT("%spool_empty.png"), *PluginTestDir), FString::Printf(TEXT("%spool_mask.png"), *PluginTestDir),TEXT("Flamingo"));
}

void AImageBase64FunctionalTest::OnCreateImageEditBase64TestComplete()
{
	TestPawn->StartCreateImageEditVariationBase64Test(FString::Printf(TEXT("%spool_empty.png"), *PluginTestDir));
}

void AImageBase64FunctionalTest::OnCreateImageEditVariationBase64TestComplete()
{
	FinishTest(EFunctionalTestResult::Succeeded, "All tests passed");
}

