// Created, maintained by Vanan A. - rezonated @ github.com

#include "Tests/Actors/FunctionalTestPawn.h"

#include "Enums/CompletionEnums.h"
#include "Proxies/CompletionProxies.h"
#include "Proxies/EditsProxies.h"
#include "Proxies/EmbeddingsProxies.h"
#include "Tests/FunctionalTests/CompletionFunctionalTest.h"
#include "Tests/FunctionalTests/EditsFunctionalTest.h"
#include "Tests/FunctionalTests/EmbeddingsFunctionalTest.h"


AFunctionalTestPawn::AFunctionalTestPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AFunctionalTestPawn::StartCreateCompletionTest(FString Prompt)
{
	if (!CreateCompletionFunctionalTest)
		return;

	if (Prompt.IsEmpty() || Prompt.Len() <= 0 || Prompt == TEXT(""))
	{
		CreateCompletionFunctionalTest->FailTest(TEXT("Prompt is empty"));
	}
	
	const auto Proxy = UCreateCompletionRequestProxy::CreateCompletion(this, Prompt, ECompletionModel::ECM_Davinci);

	if (!Proxy)
	{
		CreateCompletionFunctionalTest->FailTest(TEXT("Failed to create completion request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCompletionSuccess);

	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCompletionFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCompletionSuccess(FCreateCompletionResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		CreateCompletionFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		CreateCompletionFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (Response.choices[0].text.IsEmpty())
	{
		CreateCompletionFunctionalTest->FailTest(TEXT("No response text returned"));
		return;
	}

	CreateCompletionFunctionalTest->PassTest(FString::Printf(TEXT("Response text returned %s"), *Response.choices[0].text));
}

void AFunctionalTestPawn::OnCompletionFailure(FCreateCompletionResponse Response, FString JSONString, FString Error)
{
	CreateCompletionFunctionalTest->FailTest(TEXT("Should not fire failure delegate"));
}

void AFunctionalTestPawn::StartCreateEditsTest(FString Input, FString Instruction)
{
	if (!CreateEditsFunctionalTest)
		return;

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		CreateEditsFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	if (Instruction.IsEmpty() || Instruction.Len() <= 0 || Instruction == TEXT(""))
	{
		CreateEditsFunctionalTest->FailTest(TEXT("Instruction is empty"));
		return;
	}

	const auto Proxy = UCreateEditsRequestProxy::CreateEdits(this, Input, Instruction);

	if (!Proxy)
	{
		CreateEditsFunctionalTest->FailTest(TEXT("Failed to create edits request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnEditsSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnEditsFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnEditsSuccess(FCreateEditsResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		CreateEditsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		CreateEditsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	if (Response.choices[0].text.IsEmpty())
	{
		CreateEditsFunctionalTest->FailTest(TEXT("No response text returned"));
		return;
	}
	
	CreateEditsFunctionalTest->PassTest(FString::Printf(TEXT("Response text returned %s"), *Response.choices[0].text));
}

void AFunctionalTestPawn::OnEditsFailure(FCreateEditsResponse Response, FString JSONString, FString Error)
{
	CreateEditsFunctionalTest->FailTest(TEXT("Should not fire failure delegate"));
}

void AFunctionalTestPawn::StartCreateEmbeddingsTest(FString Input)
{
	if (!CreateEmbeddingsFunctionalTest)
	{
		return;
	}

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		CreateEmbeddingsFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	const auto Proxy = UCreateEmbeddingsRequestProxy::CreateEmbeddings(this, Input);

	if (!Proxy)
	{
		CreateEmbeddingsFunctionalTest->FailTest(TEXT("Failed to create embeddings request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnEmbeddingsSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnEmbeddingsFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnEmbeddingsSuccess(FCreateEmbeddingsResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		CreateEmbeddingsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		CreateEmbeddingsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.data.Num() < 0)
	{
		CreateEmbeddingsFunctionalTest->FailTest(TEXT("No response data returned"));
		return;
	}
	
	CreateEmbeddingsFunctionalTest->PassTest(FString::Printf(TEXT("Response data returned with length of %d"), Response.data.Num()));
}

void AFunctionalTestPawn::OnEmbeddingsFailure(FCreateEmbeddingsResponse Response, FString JSONString, FString Error)
{
	CreateEmbeddingsFunctionalTest->FailTest(TEXT("Should not fire failure delegate"));
}
