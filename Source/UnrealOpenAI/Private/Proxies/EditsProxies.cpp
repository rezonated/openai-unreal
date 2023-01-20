// Created, maintained by Vanan A. - rezonated @ github.com


#include "Proxies/EditsProxies.h"

#include "JsonObjectConverter.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

#pragma region Create Edits Proxies

UCreateEditsRequestProxy* UCreateEditsRequestProxy::CreateEdits(UObject* WorldContextObject, FString Input, FString Instruction)
{
	UCreateEditsRequestProxy* Proxy = NewObject<UCreateEditsRequestProxy>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->Input = Input;
	Proxy->Instruction = Instruction;
	return Proxy;
}

void UCreateEditsRequestProxy::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("WorldContextObject is null"));
		return;
	}

	if (Input.IsEmpty() || Input == TEXT("") || Input.Len() <= 0)
	{
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Input is empty"));
		return;
	}

	if (Instruction.IsEmpty() || Instruction == TEXT("") || Instruction.Len() <= 0)
	{
		OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Instruction is empty"));
		return;
	}

	FString JSONPayload;
	FCreateEditsRequest RequestPayload;
	RequestPayload.input = Input;
	RequestPayload.instruction = Instruction;

	FJsonObjectConverter::UStructToJsonObjectString(RequestPayload, JSONPayload, 0, 0);

	SendPayload(TEXT("edits"), JSONPayload, EHTTPMethod::EHP_POST, [this](FHttpRequestPtr, const FHttpResponsePtr Response, const bool bWasSuccessful)
	{
		if (bWasSuccessful)
		{
			FString ResponseString = Response->GetContentAsString();
			ResponseString = SanitizeString(ResponseString);

			if(FString ErrorMessage, ErrorType; CheckErrorResponse(ResponseString, ErrorMessage, ErrorType))
			{
				OnFailure.Broadcast(FCreateEditsResponse(), ResponseString, ErrorMessage);
				return;
			}

			FCreateEditsResponse EditsResponse;
			if (FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &EditsResponse, 0, 0))
			{
				OnSuccess.Broadcast(EditsResponse, Response->GetContentAsString(), TEXT(""));
			}
			else
			{
				OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Failed to convert create edits response to struct"));
			}
		}
		else
		{
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Create edits request failed"));
		}
	}, [this]
	{
			OnFailure.Broadcast(FCreateEditsResponse(), TEXT(""), TEXT("Failed to send create edits request"));
	});
}

#pragma endregion