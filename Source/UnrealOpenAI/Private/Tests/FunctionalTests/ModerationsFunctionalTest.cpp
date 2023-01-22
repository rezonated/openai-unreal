// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/ModerationsFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"

AModerationsFunctionalTest::AModerationsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AModerationsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->ModerationsFunctionalTest = this;

	TestPawn->StartModerationsTest("I want to kill them");
}
