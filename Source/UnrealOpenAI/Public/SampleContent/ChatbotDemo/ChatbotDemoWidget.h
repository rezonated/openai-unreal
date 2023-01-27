// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTypes/CompletionDataTypes.h"
#include "ChatbotDemoWidget.generated.h"

// Class to handle the widget for chatbot demo. Acts like a chatroom UI. User can type in the input and send it to the OpenAI's completion API.
UCLASS()
class UNREALOPENAI_API UChatbotDemoWidget : public UUserWidget
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
	 * Button to send the user input to OpenAI's completion API
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UButton* B_Send_Input;

	/**
	 * Text box to take user input
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UMultiLineEditableTextBox* MLETB_User_Input;

	/**
	 * Scroll box to hold and display the chat log
	 */
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UScrollBox* SB_ChatLog;

	/**
	 * Class type for the user query widget BP
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"), Category="ChatbotDemoWidget")
	const UClass* ChatbotUserQueryWidgetClass;

	/**
	 * Class type for the AI response widget BP
	 */
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"), Category="ChatbotDemoWidget")
	const UClass* ChatbotAIResponseWidgetClass;

	/**
	 * Instruction to the AI.
	 * This is the prompt that will be sent to the OpenAI's completion API
	 */
	FString Instruction;

	/**
	 * Set the instruction to the completion API via blueprint
	 * @param NewInstruction Instruction to the completion API
	 */
	UFUNCTION(BlueprintCallable, Category="ChatbotDemoWidget")
	void SetInstruction(FString NewInstruction);

	/**
	 * Callback function for the completion API when the request is successful
	 * @param Response Response struct from the completion API
	 * @param JSONString JSON string of the response
	 * @param Error Error string if any
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void OnCompletionResponse(FCreateCompletionResponse Response, FString JSONString, FString Error);

	/**
	 * Callback function for the completion API when the request fails
	 * @param Response Response struct from the completion API
	 * @param JSONString JSON string of the response
	 * @param Error Error string if any
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void OnCompletionFailed(FCreateCompletionResponse Response, FString JSONString, FString Error);

	/**
	 * Callback function for when the send input button is clicked
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void OnSendInput();

	/**
	 * Callback function for when the user input text box is changed
	 * @param Text Current text in the user input text box
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void OnUserInputChanged(const FText& Text);

	/**
	 * Add the AI response to the chat log
	 * @param AIResponse Response from the AI
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void AddAIResponse(FString AIResponse);

	/**
	 * Add the user input to the chat log
	 * @param UserInput Input from the user
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void AddUserInput(FString UserInput);

	/**
	 * Toggle the activation of user input text box and send input button
	 * @param bFlag Flag to toggle the user input
	 */
	UFUNCTION(Category="ChatbotDemoWidget")
	void ToggleUserInput(bool bFlag) const;
};
