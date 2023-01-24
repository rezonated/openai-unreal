// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "Blueprint/UserWidget.h"
#include "ChatbotDemoAIResponse.generated.h"

// Class to display the AI response inside ChatbotDemoWidget, implements basic IResponse
// interface
UCLASS()
class UNREALOPENAI_API UChatbotDemoAIResponse : public UUserWidget, public IResponse
{
	GENERATED_BODY()
public:
	/**
	 * IResponse interface implementation to set the response from AI
	 * @param Response Response to display
	 */
	virtual void SetResponse(FString Response) override;

private:
	/**
	 * Text block to display the AI response
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoAIResponse")
	class UTextBlock* TB_AI_Response;
};
