// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/FineTuneDataTypes.h"
#include "Enums/FineTuneEnums.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FineTuneProxies.generated.h"


#pragma region Create FineTune Proxy

// Delegate for the create fine tune request proxy, will return the response in
// FFineTune struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);

// Class to handle the create fine tune request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create file tune request is successful, will return the response in
	 * FFineTune struct, a JSON string response containing either a valid
	 * response or error response, and an error string when the request fails
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateFineTuneRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the create fine tune request fails, will return an empty FFineTune
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateFineTuneRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the create fine tune request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/create
	 *
	* Creates a job that fine-tunes a specified model from a given dataset.
	* Response includes details of the enqueued job including job status and the name of the fine-tuned models once complete.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param TrainingFileID The ID of an uploaded file that contains training data.
	 * Your dataset must be formatted as a JSONL file, where each training example is a
	 * JSON object with the keys "prompt" and "completion". Additionally, you must upload
	 * your file with the purpose fine-tune.
	 * @param ValidationFileID The ID of an uploaded file that contains validation data.
	* If you provide this file, the data is used to generate validation metrics
	* periodically during fine-tuning. These metrics can be viewed in the fine-tuning
	* results file. Your train and validation data should be mutually exclusive.
	* Your dataset must be formatted as a JSONL file, where each validation example is a
	* JSON object with the keys "prompt" and "completion". Additionally, you must upload
	* your file with the purpose fine-tune.
	 * @param Model he name of the base model to fine-tune. You can select one of "ada",
	 * "babbage", "curie", "davinci", or a fine-tuned model created after 2022-04-21. To
	 * learn more about these models, see the Models documentation. 
	 * @return The proxy object to use for the request 
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UCreateFineTuneProxy* CreateFineTune(UObject* WorldContextObject, FString TrainingFileID, FString ValidationFileID, EFineTuneModels Model);

	/**
	 * Activates the list files request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's training file ID
	 */
	FString TrainingFileID;

	/**
	 * Current request's validation file ID
	 */
	FString ValidationFileID;

	/**
	 * Current request's model
	 */
	EFineTuneModels Model;
};

#pragma endregion

#pragma region List FineTune Proxy

// Delegate for the create fine tune request proxy, will return the response in
// FFineTune struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFineTuneRequestCallbackSignature, FListFineTunesResponse, Response, FString, JSONString, FString, Error);

// Class to handle the create fine tune request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UListFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the list fine tune request is successful, will return the response in
	 * FFileResponse struct, a valid JSON string response, and an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FListFineTuneRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the list fine tune request fails, will return an empty FFileResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FListFineTuneRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the list fine tune request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/list
	 *
	 * List your organization's fine-tuning jobs
	 * @param WorldContextObject Function caller to obtain world context
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UListFineTuneProxy* ListFineTune(UObject* WorldContextObject);

	/**
	 * Activates the list files request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;
};

#pragma endregion

#pragma region Retrieve FineTune Proxy

// Delegate for the retrieve fine tune request proxy, will return the response in
// FFineTune struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRetrieveFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);

// Class to handle the retrieve fine tune request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API URetrieveFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the list fine tune request is successful, will return the response in
	 * FFileResponse struct, a valid JSON string response, and an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FRetrieveFineTuneRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the list fine tune request fails, will return an empty FFileResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FRetrieveFineTuneRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the retrieve fine tune request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/retrieve
	 *
	 * Gets info about the fine-tune job.
	 * @param WorldContextObject Function caller to obtain world context 
	 * @param FineTuneID The ID of the fine-tune job
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static URetrieveFineTuneProxy* RetrieveFineTune(UObject* WorldContextObject, FString FineTuneID);

	/**
	 * Activates the list files request proxy, call this function in C++ to execute the
	 * request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's fine tune ID
	 */
	FString FineTuneID;
};

#pragma endregion

#pragma region Cancel FineTune Proxy

// Delegate for the cancel fine tune request proxy, will return the response in
// FFineTune struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCancelFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);

// Class to handle the cancel fine tune request, exposes the OnSuccess and OnFailure and
// executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCancelFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	/**
	 * Fired when the cancel fine tune request is successful, will return the response in
	 * FFileResponse struct, a valid JSON string response, and an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCancelFineTuneRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the cancel fine tune request fails, will return an empty FFileResponse
	 * struct, JSON string error response, and an error string for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FCancelFineTuneRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the cancel fine tune request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/cancel
	 *
	 * Immediately cancel a fine-tune job.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param FineTuneID The ID of the fine-tune job to cancel
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UCancelFineTuneProxy* CancelFineTune(UObject* WorldContextObject, FString FineTuneID);

	/**
	 * Activates the cancel fine tune request proxy, call this function in C++ to execute
	 * the request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's fine tune ID
	 */
	FString FineTuneID;
};

#pragma endregion

#pragma region List FineTune Events Proxy

// Delegate for the list fine tune event request proxy, will return the response in
// FFineTune struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFineTuneEventsResultsRequestCallbackSignature, FListFineTuneEventsResponse, Response, FString, JSONString, FString, Error);

// Class to handle the list fine tune events request, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UListFineTuneEventsProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	/**
	 * Fired when the list fine tune events request is successful, will return the
	 * response in FListFineTuneEventsResponse struct, a valid JSON string response, and
	 * an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FListFineTuneEventsResultsRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the list fine tune events request fails, will return an empty
	 * FListFineTuneEventsResponse struct, JSON string error response, and an error string
	 * for error message
	 */
	UPROPERTY(BlueprintAssignable)
	FListFineTuneEventsResultsRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the list fine tune events request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/events
	 *
	 * Get fine-grained status updates for a fine-tune job.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param FineTuneID The ID of the fine-tune job to get events for.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UListFineTuneEventsProxy* ListFineTuneEvents(UObject* WorldContextObject, FString FineTuneID);

	/**
	 * Activates the list fine tune events request proxy, call this function in C++ to
	 * execute the request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's fine tune ID
	 */
	FString FineTuneID;
};

#pragma endregion

#pragma region Delete FineTune Model Proxy

// Delegate for the delete fine tune model request proxy, will return the response in
// FDeleteResponse struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleteFineTuneModelResultsRequestCallbackSignature, FDeleteResponse, Response, FString, JSONString, FString, Error);

// Class to handle the delete fine tune model request, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it based on the OnlineBlueprintCallProxyBase. Can be
// called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UDeleteFineTuneModelProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
	
public:
	/**
	 * Fired when the delete fine tune model request is successful, will return the
	 * response in FDeleteResponse struct, a valid JSON string response, and an empty
	 * error string
	 */
	UPROPERTY(BlueprintAssignable)
	FDeleteFineTuneModelResultsRequestCallbackSignature OnSuccess;

	/**
	 * Fired when the delete fine tune model request fails, will return an empty
	 * FDeleteResponse struct, JSON string error response, and an error string for error
	 * message
	 */
	UPROPERTY(BlueprintAssignable)
	FDeleteFineTuneModelResultsRequestCallbackSignature OnFailure;

	/**
	 * Implementation of the delete fine tune model request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/fine-tunes/delete-model
	 *
	 * Delete a fine-tuned model. You must have the Owner role in your organization.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param ModelFineTuneID The model to delete
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UDeleteFineTuneModelProxy* DeleteFineTuneModel(UObject* WorldContextObject, FString ModelFineTuneID);

	/**
	 * Activates the delete fine tune model request proxy, call this function in C++ to
	 * execute the request
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's model fine tune ID
	 */
	FString ModelFineTuneID;
};

#pragma endregion