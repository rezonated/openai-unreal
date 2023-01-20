// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/CompletionFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

ACreateCompletionFunctionalTest::ACreateCompletionFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACreateCompletionFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();
	if (!TestPawn)
	{
		FailTest(TEXT("TestPawn is not set"));
		return;
	}

	TestPawn->CreateCompletionFunctionalTest = this;

	TestPawn->StartCreateCompletionTest("Say this is a test");
}