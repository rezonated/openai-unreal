// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/EmbeddingsFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"


AEmbeddingsFunctionalTest::AEmbeddingsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AEmbeddingsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->EmbeddingsFunctionalTest = this;

	TestPawn->StartEmbeddingsTest(TEXT("The food was delicious and the waiter..."));
}


