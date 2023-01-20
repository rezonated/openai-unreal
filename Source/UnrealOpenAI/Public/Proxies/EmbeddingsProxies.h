// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/EmbeddingsDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "EmbeddingsProxies.generated.h"

/**
 * 
 */

#pragma region Create Embedding Proxies

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateEmbeddingsRequestCallbackSignature, FCreateEmbeddingsResponse, Response, FString, JSONString, FString, Error);
UCLASS()
class UNREALOPENAI_API UCreateEmbeddingsRequestProxy : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateEmbeddingsRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Unreal Open AI | Embeddings")
	static UCreateEmbeddingsRequestProxy* CreateEmbeddings(UObject* WorldContextObject, FString Input);

	virtual void Activate() override;
	
private:
	UObject* WorldContextObject;
	FString Input;
};

#pragma endregion