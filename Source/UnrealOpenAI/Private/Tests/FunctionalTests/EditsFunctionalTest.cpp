// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/EditsFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

ACreateEditsFunctionalTest::ACreateEditsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACreateEditsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->CreateEditsFunctionalTest = this;

	TestPawn->StartCreateEditsTest("What day of the wek is it?", "Fix the spelling mistakes");
}
