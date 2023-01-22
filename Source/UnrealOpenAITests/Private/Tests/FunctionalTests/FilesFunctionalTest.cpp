// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/FilesFunctionalTest.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Tests/Actors/FunctionalTestPawn.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Engine/World.h"

AFilesFunctionalTest::AFilesFunctionalTest()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFilesFunctionalTest::OnTestStartHandler()
{
	Super::OnTestStartHandler();

	if (!TestPawn)
	{
		FailTest("TestPawn is not set");
		return;
	}

	TestPawn->FilesFunctionalTest = this;

	TestPawn->StartCreateFileTest(FString::Printf(TEXT("%sPlugins/UnrealOpenAI/Content/Test/training.jsonl"), *UKismetSystemLibrary::GetProjectDirectory()));
}

void AFilesFunctionalTest::OnFileUploadTestComplete()
{
	TestPawn->StartListFilesTest();
}

void AFilesFunctionalTest::OnListFilesTestComplete(FString ID)
{
	TestPawn->StartRetrieveFileTest(ID);
}

void AFilesFunctionalTest::OnRetrieveFileTestComplete(FString ID)
{
	// Skip retrieve file content test for now due to it being a paid feature
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda([&]
	{
		TestPawn->StartDeleteFileTest(ID);
	});

	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, 10, false);
}

void AFilesFunctionalTest::OnDeleteFileTestComplete()
{
	FinishTest(EFunctionalTestResult::Succeeded, "All files functional tests passed");
}