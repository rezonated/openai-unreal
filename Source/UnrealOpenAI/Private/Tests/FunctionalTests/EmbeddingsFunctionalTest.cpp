// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/EmbeddingsFunctionalTest.h"

#include "Tests/Actors/FunctionalTestPawn.h"


ACreateEmbeddingsFunctionalTest::ACreateEmbeddingsFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ACreateEmbeddingsFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->CreateEmbeddingsFunctionalTest = this;

	TestPawn->StartCreateEmbeddingsTest(TEXT("The food was delicious and the waiter..."));
}


