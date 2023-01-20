// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/FineTuneDataTypes.h"
#include "Enums/FineTuneEnums.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "FineTuneProxies.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UCreateFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateFineTuneRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateFineTuneRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UCreateFineTuneProxy* CreateFineTune(UObject* WorldContextObject, FString TrainingFileID, FString ValidationFileID, EFineTuneModels Model);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString TrainingFileID;
	FString ValidationFileID;
	EFineTuneModels Model;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFineTuneRequestCallbackSignature, FListFineTunesResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UListFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FListFineTuneRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListFineTuneRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UListFineTuneProxy* ListFineTune(UObject* WorldContextObject);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FRetrieveFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API URetrieveFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FRetrieveFineTuneRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRetrieveFineTuneRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static URetrieveFineTuneProxy* RetrieveFineTune(UObject* WorldContextObject, FString FineTuneID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FineTuneID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCancelFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UCancelFineTuneProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FCancelFineTuneRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCancelFineTuneRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UCancelFineTuneProxy* CancelFineTune(UObject* WorldContextObject, FString FineTuneID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FineTuneID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListFineTuneEventsResultsRequestCallbackSignature, FListFineTuneEventsResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UListFineTuneEventsProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FListFineTuneEventsResultsRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListFineTuneEventsResultsRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UListFineTuneEventsProxy* ListFineTuneEvents(UObject* WorldContextObject, FString FineTuneID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FineTuneID;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FDeleteFineTuneModelResultsRequestCallbackSignature, FDeleteResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UDeleteFineTuneModelProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FDeleteFineTuneModelResultsRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteFineTuneModelResultsRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "OpenAI|FineTune") static UDeleteFineTuneModelProxy* DeleteFineTuneModel(UObject* WorldContextObject, FString FineTuneID);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString FineTuneID;
};