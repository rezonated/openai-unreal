// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CompletionDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "CompletionProxies.generated.h"

#pragma region Create Completion Proxy

// Delegate for the create completion request proxy, will return the response in
// FCreateCompletionResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateCompletionRequestCallbackSignature, FCreateCompletionResponse, Response, FString, JSONString, FString, Error);

// Class to handle the create completion request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateCompletionRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create completion request is successful, will return the
	 * response in FCreateCompletionResponse struct, a valid JSON string response and an
	 * empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create completion request fails, will return an empty
	 * FCreateCompletionResponse struct, JSON string error response, and an error string
	 * for error message  
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateCompletionRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create completion request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/completions/create
	 * 
	 * Given a prompt, the model will return predicted completions, and can also return the
	 * probabilities of alternative tokens at each position.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Prompt The prompt(s) to generate completions for, encoded as strings, array
	 * of tokens or array of token arrays. Defaults to <|endoftext|>.
	 * @param CompletionModel The completion model to use. 
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Completion")
	static UCreateCompletionRequestProxy* CreateCompletion(UObject* WorldContextObject, FString Prompt, ECompletionModel CompletionModel);

	/**
	 * Activates the create embeddings request proxy, call this function in C++ to execute
	 * the request
	 */
	virtual void Activate() override;

private:
	/**
	 *  Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 *  Current prompt to generate completions for
	 */
	FString Prompt;

	/**
	 *  Completion model to use
	 */
	ECompletionModel CompletionModel;
};

#pragma endregion