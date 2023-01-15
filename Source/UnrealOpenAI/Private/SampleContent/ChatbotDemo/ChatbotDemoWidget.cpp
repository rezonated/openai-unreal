// Created, maintained by Vanan A. - rezonated @ github.com


#include "SampleContent/ChatbotDemo/ChatbotDemoWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Proxies/CompletionProxies.h"
#include "SampleContent/ChatbotDemo/ChatbotDemoAIResponse.h"
#include "SampleContent/ChatbotDemo/ChatbotDemoUserQuery.h"
#include "UnrealOpenAI/Public/Utils/Utils.h"

void UChatbotDemoWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (B_Send_Input)
	{
		B_Send_Input->OnClicked.AddDynamic(this, &UChatbotDemoWidget::OnSendInput);
	}

	if (MLETB_User_Input)
	{
		MLETB_User_Input->SetKeyboardFocus();

		MLETB_User_Input->OnTextChanged.AddDynamic(this, &UChatbotDemoWidget::OnUserInputChanged);
	}

	
}



void UChatbotDemoWidget::OnSendInput()
{
	if (MLETB_User_Input->GetText().ToString().Len() <= 0)
	{
		return;
	}

	AddUserInput(MLETB_User_Input->GetText().ToString());

	Instruction += MLETB_User_Input->GetText().ToString() + LINE_TERMINATOR + "A: ";

	const auto CreateCompletionRequest = UCreateCompletionProxies::CreateCompletion(this, Instruction, ECompletionModel::ECM_Davinci);
	
	CreateCompletionRequest->OnSuccess.AddDynamic(this, &UChatbotDemoWidget::OnCompletionResponse);
	CreateCompletionRequest->OnFailure.AddDynamic(this, &UChatbotDemoWidget::OnCompletionFailed);

	CreateCompletionRequest->Activate();

	MLETB_User_Input->SetText(FText::FromString(TEXT("")));

	ToggleUserInput(false);
}

void UChatbotDemoWidget::AddAIResponse(FString AIResponse)
{
	if (SB_ChatLog)
	{
		auto ChatbotDemoAIResponse =
		NewObject<UChatbotDemoAIResponse>(SB_ChatLog, ChatbotAIResponseWidgetClass);
		if (ChatbotDemoAIResponse)
		{
			SB_ChatLog->AddChild(ChatbotDemoAIResponse);

			auto ChatbotDemoAIResponseScrollBoxSlot = UWidgetLayoutLibrary::SlotAsScrollBoxSlot(ChatbotDemoAIResponse);

			if (ChatbotDemoAIResponseScrollBoxSlot)
			{
				ChatbotDemoAIResponseScrollBoxSlot->SetPadding(FMargin(20.f));
				ChatbotDemoAIResponseScrollBoxSlot->SetHorizontalAlignment(HAlign_Left);
			}
			
			ChatbotDemoAIResponse->SetResponse(AIResponse);
		}	
	}
}

void UChatbotDemoWidget::AddUserInput(FString UserInput)
{
	if (SB_ChatLog)
	{
		auto ChatbotDemoQueryUserInput = NewObject<UChatbotDemoUserQuery>(SB_ChatLog, ChatbotUserQueryWidgetClass);

		if (ChatbotDemoQueryUserInput)
		{
			SB_ChatLog->AddChild(ChatbotDemoQueryUserInput);
			
			auto ChatboxDemoQueryUserInputScrollBoxSlot = UWidgetLayoutLibrary::SlotAsScrollBoxSlot(ChatbotDemoQueryUserInput);
			if (ChatboxDemoQueryUserInputScrollBoxSlot)
			{
				ChatboxDemoQueryUserInputScrollBoxSlot->SetPadding(FMargin(20.f));
				ChatboxDemoQueryUserInputScrollBoxSlot->SetHorizontalAlignment(HAlign_Right);
			}
			ChatbotDemoQueryUserInput->SetResponse(UserInput);
		}
	}
}

void UChatbotDemoWidget::ToggleUserInput(const bool bFlag) const
{
	if (B_Send_Input)
	{
		B_Send_Input->SetIsEnabled(bFlag);
	}

	if (MLETB_User_Input)
	{
		MLETB_User_Input->SetIsEnabled(bFlag);
	}

	bFlag ? MLETB_User_Input->SetKeyboardFocus() : UWidgetBlueprintLibrary::SetFocusToGameViewport();
}

void UChatbotDemoWidget::SetInstruction(FString NewInstruction)
{
	Instruction = NewInstruction;

	Instruction.Append(NewInstruction);
	Instruction.Append(LINE_TERMINATOR);
	Instruction.Append(TEXT("Q: "));
}

void UChatbotDemoWidget::OnCompletionResponse(FCreateCompletionResponse Response, FString JSONString)
{
	AddAIResponse(Response.choices.text);
	Instruction += Response.choices.text + LINE_TERMINATOR + "Q: ";
	ToggleUserInput(true);

	if (SB_ChatLog)
	{
		SB_ChatLog->ScrollToEnd();
	}
}

void UChatbotDemoWidget::OnCompletionFailed(FCreateCompletionResponse Response, FString JSONString)
{
	ToggleUserInput(true);
}

void UChatbotDemoWidget::OnUserInputChanged(const FText& Text)
{
	if (Text.ToString().EndsWith(LINE_TERMINATOR))
	{
		auto TextBoxString = MLETB_User_Input->GetText().ToString();

		TextBoxString = SanitizeString(TextBoxString);

		MLETB_User_Input->SetText(FText::FromString(TextBoxString));

		OnSendInput();
	}
}
