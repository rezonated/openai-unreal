// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DataTypes/DataTypes.h"
#include "Enums/Enums.h"
#include "CreateImageWidget.generated.h"

/**
 * 
 */
UCLASS()
class UNREALOPENAI_API UCreateImageWidget : public UUserWidget
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
	class UImage* I_Response;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadOnly)
	EImageSize ImageSize = EImageSize::EIS_1024;

	UFUNCTION()
	void OnUserInputChanged(const FText& Text);
	
	UFUNCTION()
	void OnSendInput();
	
	UFUNCTION()
	void OnImageRequestCompleteURL(FCreateImageResponseURL Response, FString JSONString);

	UFUNCTION()
	void OnImageRequestComplete(UTexture2D* Texture2D);
};
