// Created, maintained by Vanan A. - rezonated @ github.com


#include "Tests/FunctionalTests/OpenAIFunctionalTestBase.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Utils/Utils.h"

AOpenAIFunctionalTestBase::AOpenAIFunctionalTestBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOpenAIFunctionalTestBase::OnTestPrepareHandler()
{
	PrintDebugLogAndOnScreen("OnTestPrepareHandler");

	StartTest();
}

void AOpenAIFunctionalTestBase::BeginPlay()
{
	Super::BeginPlay();

	PrintDebugLogAndOnScreen("BeginPlay");

	OnTestPrepare.AddDynamic(this, &AOpenAIFunctionalTestBase::OnTestPrepareHandler);

	OnTestStart.AddDynamic(this, &AOpenAIFunctionalTestBase::OnTestStartHandler);
}

void AOpenAIFunctionalTestBase::OnTestStartHandler()
{
	PrintDebugLogAndOnScreen("Test started");
}

void AOpenAIFunctionalTestBase::PrepareTest()
{
	Super::PrepareTest();

	PrintDebugLogAndOnScreen("PrepareTest");
}

bool AOpenAIFunctionalTestBase::IsReady_Implementation()
{
	return true;
}

void AOpenAIFunctionalTestBase::StartTest()
{
	Super::StartTest();

	PrintDebugLogAndOnScreen("StartTest");
}

void AOpenAIFunctionalTestBase::FailTest(FString Message)
{
	FinishTest(EFunctionalTestResult::Failed, Message);
	
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}

void AOpenAIFunctionalTestBase::PassTest(FString Message)
{
	FinishTest(EFunctionalTestResult::Succeeded, Message);
	
	UKismetSystemLibrary::QuitGame(GetWorld(), UGameplayStatics::GetPlayerController(GetWorld(), 0), EQuitPreference::Quit, false);
}


