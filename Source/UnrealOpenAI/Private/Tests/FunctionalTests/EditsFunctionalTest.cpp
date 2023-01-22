// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/EditsFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

AEditsFunctionalTest::AEditsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEditsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->EditsFunctionalTest = this;

	TestPawn->StartEditsTest("What day of the wek is it?", "Fix the spelling mistakes");
}
