// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/EditsDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "EditsProxies.generated.h"

/**
 * 
 */
#pragma region Create Edits Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateEditsRequestCallbackSignature, FCreateEditsResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UCreateEditsRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateEditsRequestCallbackSignature OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FCreateEditsRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Edits")
	static UCreateEditsRequestProxy* CreateEdits(UObject* WorldContextObject, FString Input, FString Instruction);

	virtual void Activate() override;

private:
	UObject* WorldContextObject;
	FString Input;
	FString Instruction;
};

#pragma endregion