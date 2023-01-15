// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/ModerationDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ModerationProxies.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateModerationRequestCallbackSignature, FCreateModerationResponse, Response, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateModerationRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateModerationRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateModerationRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI")
		static UCreateModerationRequestProxy* CreateModerationRequest(UObject* WorldContextObject, FString Input, EModerationModels Model);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Input;
	EModerationModels Model;

	FCreateModerationResponse Response;
	FString JSONString;
};
