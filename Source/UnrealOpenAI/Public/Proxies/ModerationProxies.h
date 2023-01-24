// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/ModerationDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ModerationProxies.generated.h"

#pragma region Create Moderation Proxies

// Delegate for the create moderation request proxy, will return the response in
// FCreateModerationResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateModerationRequestCallbackSignature, FCreateModerationResponse, Response, FString, JSONString, FString, Error);

// Class to handle the create moderation request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateModerationRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create moderation request is successful, will return the response in
	 * FCreateModerationResponse struct, a valid JSON string response and an empty error
	 * string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateModerationRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create moderation request fails, will return an empty
	 * FCreateModerationResponse struct, JSON string error response, and an error string
	 * for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateModerationRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create moderation request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/moderations/create
	 *
	 * Given a input text, outputs if the model classifies it as violating OpenAI's content
	 * policy.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Input The input text to classify
	 * @param Model Two content moderations models are available: text-moderation-stable and
	 * text-moderation-latest.
	 * The default is text-moderation-latest which will be automatically upgraded over time.
	 * This ensures you are always using our most accurate model.
	 * If you use text-moderation-stable, we will provide advanced notice before
	 * updating the model. Accuracy of text-moderation-stable may be slightly lower than for
	 * text-moderation-latest.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Moderation")
	static UCreateModerationRequestProxy* CreateModerationRequest(UObject* WorldContextObject, FString Input, EModerationModels Model);

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
	 * Current input text to classify
	 */
	FString Input;

	/**
	 * Current model to use for the moderation request
	 */
	EModerationModels Model;
};

#pragma endregion