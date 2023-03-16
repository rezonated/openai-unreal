// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/ChatDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ChatProxies.generated.h"

// Delegate for the create completion request proxy, will return the response in
// FChatResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FChatCompletionRequestCallbackSignature, FChatResponse, Response, FString, JSONString, FString, Error);

// Class to handle the chat request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UChatProxies : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	/**
	 * Fired when the chat request is successful, will return the
	 * response in FChatResponse struct, a valid JSON string
	 * response and an empty error string 
	 */
	UPROPERTY(BlueprintAssignable)
	FChatCompletionRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the chat request fails, will return an empty
	 * FChatResponse struct, JSON string error response, and an
	 * error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FChatCompletionRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the chat request API call as defined in:
	 * https://platform.openai.com/docs/api-reference/chat
	 *
	 * Given an array of chain of messages, the model will return
	 * a response in form of completion of the last message in the
	 * chain.
	 *  
	 * @param WorldContextObject Function caller to obtain world
	 * context 
	 * @param Model The chat model to use. 
	 * @param Messages  The messages to generate completions for
	 * @return  The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Chat")
	static UChatProxies* Chat(UObject* WorldContextObject, FString Model, TArray<FMessage> Messages);

	/**
	 * Activates the chat request proxy, call this function in C++
	 * to execute the request
	 */
	virtual void Activate() override;

private:
	/**
	 * The world context object, used to obtain the world context
	 */
	UObject* WorldContextObject;

	/**
	 * The chat model to use
	 */
	FString Model;

	/**
	 * The messages to generate completions for
	 */
	TArray<FMessage> Messages;
};
