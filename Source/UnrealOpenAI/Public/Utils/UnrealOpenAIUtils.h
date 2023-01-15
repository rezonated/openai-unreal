// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Net/OnlineBlueprintCallProxyBase.h"

#include "UnrealOpenAIUtils.generated.h"
/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtils : public UObject
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	static bool OpenImageDialog(FString DialogTitle, TArray<uint8>& OutFileData);


	UFUNCTION(BlueprintCallable)
	static bool ConvertToTexture2D(TArray<uint8>FileData, UTexture2D*& OutTexture);
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGetImageFromURLRequestCallbackSignature, UTexture2D*, Texture2D);
UCLASS()
class UNREALOPENAI_API UUnrealOpenAIUtilsGetImageFromURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnSuccess;
	UPROPERTY(BlueprintAssignable)
	FGetImageFromURLRequestCallbackSignature OnFailure;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAIUtils - GetImageFromURL")
	static UUnrealOpenAIUtilsGetImageFromURL* GetImageFromURL(UObject* WorldContextObject, FString URL);

	virtual void Activate() override;

private:
	void OnProcessRequestComplete(TSharedPtr<class IHttpRequest, ESPMode::ThreadSafe> HttpRequest, TSharedPtr<class IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bArg);
	
	UObject* WorldContextObject;
	FString URL;

	UPROPERTY(Transient)
	UTexture2D* Texture2D;
};