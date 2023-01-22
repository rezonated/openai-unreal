// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/CompletionFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

ACompletionsFunctionalTest::ACompletionsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACompletionsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();
	if (!TestPawn)
	{
		FailTest(TEXT("TestPawn is not set"));
		return;
	}

	TestPawn->CompletionsFunctionalTest = this;

	TestPawn->StartCompletionsTest("Say this is a test");
}