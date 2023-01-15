// Created, maintained by Vanan A. - rezonated @ github.com


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
