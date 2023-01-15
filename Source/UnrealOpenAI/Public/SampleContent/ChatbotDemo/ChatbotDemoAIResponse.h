// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "Blueprint/UserWidget.h"
#include "ChatbotDemoAIResponse.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UChatbotDemoAIResponse : public UUserWidget, public IResponse
{
	GENERATED_BODY()
public:
	virtual void SetResponse(FString Response) override;

private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly)
	class UTextBlock* TB_AI_Response;
};
