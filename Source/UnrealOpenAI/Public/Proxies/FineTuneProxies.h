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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString);
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

	FFineTune Response;
	FString JSONString;	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListFineTuneRequestCallbackSignature, FListFineTunesResponse, Response, FString, JSONString);
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

	FListFineTunesResponse Response;
	FString JSONString;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRetrieveFineTuneRequestCallbackSignature, FFineTune, Response, FString, JSONString);
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

	FFineTune Response;
	FString JSONString;
};