// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/EditsDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "EditsProxies.generated.h"

#pragma region Create Edits Proxies

// Delegate for the create edits request proxy, will return the response in
// FCreateEditsResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateEditsRequestCallbackSignature, FCreateEditsResponse, Response, FString, JSONString, FString, Error);

// Class to handle the create edits request proxy, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase. Can
// be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateEditsRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create edits request is successful, will return the response in
	 * FCreateEditsResponse struct, a valid JSON string response and an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateEditsRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create edits request fails, will return an empty FCreateEditsResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateEditsRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create edits request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/edits/create
	 *
	 * Given a prompt and an instruction, the model will return an edited version of the
	 * prompt.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Input The input text to use for the edit.
	 * @param Instruction The instruction that tells the model how to edit the prompt.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Edits")
	static UCreateEditsRequestProxy* CreateEdits(UObject* WorldContextObject, FString Input, FString Instruction);

	/**
	 * Activates the create embeddings request proxy, call this function in C++ to execute
	 * the request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current input to use for the edit
	 */
	FString Input;

	/**
	 * Current instruction to use for the edit
	 */
	FString Instruction;
};

#pragma endregion