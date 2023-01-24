// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ImageEnums.h"
#include "CreateImageWidget.generated.h"

// Class to display widget for create image demo, user can type in a prompt for an image
// that they want to generate and send it to crate image API
UCLASS()
class UNREALOPENAI_API UCreateImageWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/**
	 * Native construct override to initialize the widget, used to initialize send input
	 * button and user input text box
	 */
	virtual void NativeConstruct() override;
	
private:
	/**
	 * Button to send the user input to OpenAI's image API
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UButton* B_Send_Input;

	/**
	 * Text box to take user input
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UMultiLineEditableTextBox* MLETB_User_Input;

	/**
	 * Image response from the API
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UImage* I_Response;

	/**
	 * Image size to request to the API
	 */
	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	EImageSize ImageSize = EImageSize::EIS_1024;

	/**
	 * Callback function for when the user input text box changes
	 * @param Text Current text in the user input text box
	 */
	UFUNCTION(Category="CreateImageWidget")
	void OnUserInputChanged(const FText& Text);

	/**
	 * Callback function for when the user clicks the send input button
	 */
	UFUNCTION(Category="CreateImageWidget")
	void OnSendInput();

	/**
	 * Callback function for when the image API request is complete
	 * @param Response Response struct from the API
	 * @param JSONString JSON string from the image API
	 * @param Error Error string if any
	 */
	UFUNCTION(Category="CreateImageWidget")
	void OnImageRequestCompleteURL(FCreateImageResponseURL Response, FString JSONString, FString Error);

	/**
	 * Callback function for when the image API request is complete
	 * @param Texture2D Image texture from the API in the form of a texture2D
	 */
	UFUNCTION(Category="CreateImageWidget")
	void OnImageRequestComplete(UTexture2D* Texture2D);
};
