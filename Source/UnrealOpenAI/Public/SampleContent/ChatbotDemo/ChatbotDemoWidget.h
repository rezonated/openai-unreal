// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTypes/DataTypes.h"
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
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly)
	class UButton* B_Send_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly)
	class UMultiLineEditableTextBox* MLETB_User_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly)
	class UScrollBox* SB_ChatLog;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))
	const UClass* ChatbotUserQueryWidgetClass;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess="true"))
	const UClass* ChatbotAIResponseWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess="true"))
	FString Instruction;

	UFUNCTION()
	void OnCompletionResponse(FCreateCompletionResponse Response, FString JSONString);

	UFUNCTION()
	void OnCompletionFailed(FCreateCompletionResponse Response, FString JSONString);
	
	UFUNCTION()
	void OnSendInput();

	UFUNCTION()
	void OnUserInputChanged(const FText& Text);

	UFUNCTION()
	void AddAIResponse(FString AIResponse);

	UFUNCTION()
	void AddUserInput(FString UserInput);

	UFUNCTION()
	void ToggleUserInput(bool bFlag) const;
};
