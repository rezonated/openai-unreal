// Fill out your copyright notice in the Description page of Project Settings.

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
	UPROPERTY(meta = (BindWidget), VisibleAnywhere)
	class UTextBlock* TB_User_Query;
};
