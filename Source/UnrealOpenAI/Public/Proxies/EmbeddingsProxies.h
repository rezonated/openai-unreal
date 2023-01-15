// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/EmbeddingsDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "EmbeddingsProxies.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateEmbeddingsRequestCallbackSignature, FCreateEmbeddingsResponse, Response, FString, JSONString);
UCLASS()
class UNREALOPENAI_API UCreateEmbeddingsProxies : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Unreal Open AI - Embeddings")
	static UCreateEmbeddingsProxies* CreateEmbeddings(UObject* WorldContextObject, FString Input);

	virtual void Activate() override;
	
private:
	UObject* WorldContextObject;
	FString Input;

	FCreateEmbeddingsResponse Response;
	FString JSONString;
};
