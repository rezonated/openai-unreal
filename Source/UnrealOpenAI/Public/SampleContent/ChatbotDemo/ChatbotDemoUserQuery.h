// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "Blueprint/UserWidget.h"
#include "ChatbotDemoUserQuery.generated.h"

// Class to display the user query inside ChatbotDemoWidget, implements basic IResponse
// interface
UCLASS()
class UNREALOPENAI_API UChatbotDemoUserQuery : public UUserWidget, public IResponse
{
	GENERATED_BODY()
public:
	/**
	 * IResponse interface implementation to set the response from User's query
	 * @param Response Response to display
	 */
	virtual void SetResponse(FString Response) override;

private:
	/**
	 * Text block to display the user query
	 */
	UPROPERTY(meta = (BindWidget), VisibleAnywhere, Category="ChatbotDemoUserQuery")
	class UTextBlock* TB_User_Query;
};
