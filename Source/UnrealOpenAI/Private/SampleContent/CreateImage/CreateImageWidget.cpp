// Created, maintained by Vanan A. - rezonated @ github.com


#include "SampleContent/CreateImage/CreateImageWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/MultiLineEditableTextBox.h"
#include "Proxies/ImageProxies.h"
#include "Utils/UnrealOpenAIUtils.h"
#include "Utils/Utils.h"

void UCreateImageWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (B_Send_Input)
	{
		B_Send_Input->OnClicked.AddDynamic(this, &UCreateImageWidget::OnSendInput);
	}

	if (MLETB_User_Input)
	{
		MLETB_User_Input->SetKeyboardFocus();
		MLETB_User_Input->OnTextChanged.AddDynamic(this, &UCreateImageWidget::OnUserInputChanged);
	}
}

void UCreateImageWidget::OnUserInputChanged(const FText& Text)
{
	if (Text.ToString().EndsWith(LINE_TERMINATOR))
	{
		auto TextBoxString = MLETB_User_Input->GetText().ToString();

		TextBoxString = SanitizeString(TextBoxString);

		MLETB_User_Input->SetText(FText::FromString(TextBoxString));

		OnSendInput();
	}
}

void UCreateImageWidget::OnSendInput()
{
	if (MLETB_User_Input && MLETB_User_Input->GetText().ToString().Len() > 0)
	{
		const auto ImageRequestURL = UCreateImageRequestURL::CreateImageURL(this, MLETB_User_Input->GetText().ToString(), ImageSize);

		ImageRequestURL->OnImageRequestCompleteURL.AddDynamic(this, &UCreateImageWidget::OnImageRequestCompleteURL);

		ImageRequestURL->Activate();

		UWidgetBlueprintLibrary::SetFocusToGameViewport();

		MLETB_User_Input->SetIsEnabled(false);
		MLETB_User_Input->SetText(FText::FromString(TEXT("")));
		B_Send_Input->SetIsEnabled(false);
	}
}

void UCreateImageWidget::OnImageRequestCompleteURL(FCreateImageResponseURL Response, FString JSONString)
{
	const auto GetImageFromURL = UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(this, Response.data[0].url);
	
	GetImageFromURL->OnSuccess.AddDynamic(this, &UCreateImageWidget::OnImageRequestComplete);
	GetImageFromURL->Activate();
}

void UCreateImageWidget::OnImageRequestComplete(UTexture2D* Texture2D)
{
	if (Texture2D && I_Response)
	{
		I_Response->SetBrushFromTexture(Texture2D);
		I_Response->SetColorAndOpacity(FLinearColor::White);

		MLETB_User_Input->SetIsEnabled(true);
		MLETB_User_Input->SetKeyboardFocus();
		B_Send_Input->SetIsEnabled(true);
	}
}
