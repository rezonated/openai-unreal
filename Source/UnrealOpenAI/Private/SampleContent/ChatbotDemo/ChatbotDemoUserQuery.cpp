// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleContent/ChatbotDemo/ChatbotDemoUserQuery.h"

#include "Components/TextBlock.h"

void UChatbotDemoUserQuery::SetResponse(FString Response)
{
	IResponse::SetResponse(Response);

	if (TB_User_Query)
	{
		TB_User_Query->SetText(FText::FromString(Response));
	}
}
