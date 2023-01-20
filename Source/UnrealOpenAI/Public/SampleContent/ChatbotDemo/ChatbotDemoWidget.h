// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChatbotDemoWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UChatbotDemoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UButton* B_Send_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UMultiLineEditableTextBox* MLETB_User_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="ChatbotDemoWidget")
	class UScrollBox* SB_ChatLog;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"), Category="ChatbotDemoWidget")
	const UClass* ChatbotUserQueryWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"), Category="ChatbotDemoWidget")
	const UClass* ChatbotAIResponseWidgetClass;
	
	FString Instruction;

	UFUNCTION(BlueprintCallable, Category="ChatbotDemoWidget")
	void SetInstruction(FString NewInstruction);

	UFUNCTION(Category="ChatbotDemoWidget")
	void OnCompletionResponse(FCreateCompletionResponse Response, FString JSONString, FString Error);

	UFUNCTION(Category="ChatbotDemoWidget")
	void OnCompletionFailed(FCreateCompletionResponse Response, FString JSONString, FString Error);
	
	UFUNCTION(Category="ChatbotDemoWidget")
	void OnSendInput();

	UFUNCTION(Category="ChatbotDemoWidget")
	void OnUserInputChanged(const FText& Text);

	UFUNCTION(Category="ChatbotDemoWidget")
	void AddAIResponse(FString AIResponse);

	UFUNCTION(Category="ChatbotDemoWidget")
	void AddUserInput(FString UserInput);

	UFUNCTION(Category="ChatbotDemoWidget")
	void ToggleUserInput(bool bFlag) const;
};
