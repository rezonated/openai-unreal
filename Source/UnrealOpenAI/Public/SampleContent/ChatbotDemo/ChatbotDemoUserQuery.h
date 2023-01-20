// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Response.h"
#include "Blueprint/UserWidget.h"
#include "ChatbotDemoUserQuery.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UChatbotDemoUserQuery : public UUserWidget, public IResponse
{
	GENERATED_BODY()
public:
	virtual void SetResponse(FString Response) override;

private:
	UPROPERTY(meta = (BindWidget), VisibleAnywhere, Category="ChatbotDemoUserQuery")
	class UTextBlock* TB_User_Query;
};
