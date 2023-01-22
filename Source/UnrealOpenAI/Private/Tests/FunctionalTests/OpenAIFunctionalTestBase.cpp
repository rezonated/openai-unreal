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
	StartTest();
}

void AOpenAIFunctionalTestBase::BeginPlay()
{
	Super::BeginPlay();

	OnTestPrepare.AddDynamic(this, &AOpenAIFunctionalTestBase::OnTestPrepareHandler);

	OnTestStart.AddDynamic(this, &AOpenAIFunctionalTestBase::OnTestStartHandler);
}

void AOpenAIFunctionalTestBase::OnTestStartHandler()
{
	
}

void AOpenAIFunctionalTestBase::PrepareTest()
{
	Super::PrepareTest();
}

bool AOpenAIFunctionalTestBase::IsReady_Implementation()
{
	return true;
}

void AOpenAIFunctionalTestBase::StartTest()
{
	Super::StartTest();
}

void AOpenAIFunctionalTestBase::FinishTest(EFunctionalTestResult TestResult, const FString& Message)
{
	Super::FinishTest(TestResult, Message);

	PrintDebugLogAndOnScreen(TestResult == EFunctionalTestResult::Succeeded ? "Test passed" : "Test failed");
	PrintDebugLogAndOnScreen(Message);

	Destroy();
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


