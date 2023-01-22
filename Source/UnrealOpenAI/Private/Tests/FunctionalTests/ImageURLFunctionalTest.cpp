// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/ImageURLFunctionalTest.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Tests/Actors/FunctionalTestPawn.h"

AImageURLFunctionalTest::AImageURLFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AImageURLFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->ImageURLFunctionalTest = this;

	TestPawn->StartCreateImageURLTest(TEXT("A cute baby sea otter"));
}

void AImageURLFunctionalTest::OnCreateImageURLTestComplete()
{
	TestPawn->StartCreateImageEditURLTest(FString::Printf(TEXT("%spool_empty.png"), *PluginTestDir), FString::Printf(TEXT("%spool_mask.png"), *PluginTestDir),TEXT("Flamingo"));
}

void AImageURLFunctionalTest::OnCreateImageEditURLTestComplete()
{
	TestPawn->StartCreateImageEditVariationURLTest(FString::Printf(TEXT("%spool_empty.png"), *PluginTestDir));
}

void AImageURLFunctionalTest::OnCreateImageEditVariationURLTestComplete()
{
	FinishTest(EFunctionalTestResult::Succeeded, "All tests passed");
}
