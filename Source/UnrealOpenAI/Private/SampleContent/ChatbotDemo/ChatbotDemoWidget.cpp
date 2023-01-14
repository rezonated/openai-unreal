// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleContent/ChatbotDemo/ChatbotDemoWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "HTTP/UnrealOpenAIHTTP.h"
#include "SampleContent/ChatbotDemo/ChatbotDemoAIResponse.h"
#include "SampleContent/ChatbotDemo/ChatbotDemoUserQuery.h"

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

	Instruction.Append(TEXT("Act as a random stranger in a chat room and reply to the questions."));
	Instruction.Append(LINE_TERMINATOR);
	Instruction.Append(TEXT("Q: "));
}



void UChatbotDemoWidget::OnSendInput()
{
	if (MLETB_User_Input->GetText().ToString().Len() <= 0)
	{
		return;
	}

	AddUserInput(MLETB_User_Input->GetText().ToString());

	Instruction += MLETB_User_Input->GetText().ToString() + LINE_TERMINATOR + "A: ";

	const auto CreateCompletionRequest = UUnrealOpenAIHTTPCompletionRequest::CreateCompletion(this, Instruction, ECompletionModel::ECM_Davinci);
	
	CreateCompletionRequest->OnCompletionRequestComplete.AddDynamic(this, &UChatbotDemoWidget::OnCompletionResponse);
	CreateCompletionRequest->OnCompletionRequestFailed.AddDynamic(this, &UChatbotDemoWidget::OnCompletionFailed);

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

void UChatbotDemoWidget::OnCompletionResponse(FCreateCompletionResponse Response, FString JSONString)
{
	AddAIResponse(Response.choices.text);
	Instruction += Response.choices.text + LINE_TERMINATOR + "Q: ";
	ToggleUserInput(true);
}

void UChatbotDemoWidget::OnCompletionFailed(FCreateCompletionResponse Response, FString JSONString)
{
	ToggleUserInput(true);
}

void UChatbotDemoWidget::OnUserInputChanged(const FText& Text)
{
	if (Text.ToString().EndsWith(TEXT("\n")))
	{
		auto TextBoxString = MLETB_User_Input->GetText().ToString();

		TextBoxString.ReplaceInline(TEXT("\n"), TEXT(""), ESearchCase::IgnoreCase);

		MLETB_User_Input->SetText(FText::FromString(TextBoxString));

		OnSendInput();
	}
}
