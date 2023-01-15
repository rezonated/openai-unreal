// Created, maintained by Vanan A. - rezonated @ github.com


#include "SampleContent/ChatbotDemo/ChatbotDemoAIResponse.h"

#include "Components/TextBlock.h"

void UChatbotDemoAIResponse::SetResponse(FString Response)
{
	IResponse::SetResponse(Response);
	if (TB_AI_Response)
	{
		TB_AI_Response->SetText(FText::FromString(Response));
	}
}

