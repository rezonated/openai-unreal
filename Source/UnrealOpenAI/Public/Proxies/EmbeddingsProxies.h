// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/EmbeddingsDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "EmbeddingsProxies.generated.h"

#pragma region Create Embedding Proxies

// Delegate for the create embeddings request proxy, will return the response in
// FCreateEmbeddingsResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateEmbeddingsRequestCallbackSignature, FCreateEmbeddingsResponse, Response, FString, JSONString, FString, Error);

// Class to handle the create embeddings request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateEmbeddingsRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create embeddings request is successful, will return the response in
	 * FCreateEmbeddingsResponse struct, a valid JSON string response and an empty error
	 * string 
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create embeddings request fails, will return an empty
	 * FCreateEmbeddingsResponse struct, JSON string error response, and an error string for
	 * error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create embeddings request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/embeddings/create
	 *
	 * Get a vector representation of a given input that can be easily consumed by machine
	 * learning models and algorithms.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Input Input text to get embeddings for, encoded as a string or array of
	 * tokens. To get embeddings for multiple inputs in a single request, pass an array of
	 * strings or array of token arrays. Each input must not exceed 8192 tokens in length.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Unreal Open AI | Embeddings")
	static UCreateEmbeddingsRequestProxy* CreateEmbeddings(UObject* WorldContextObject, FString Input);

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
	 * Current input to get embeddings for
	 */
	FString Input;
};

#pragma endregion