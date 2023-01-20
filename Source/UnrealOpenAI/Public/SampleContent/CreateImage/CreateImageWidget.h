// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Enums/ImageEnums.h"
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
	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UButton* B_Send_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UMultiLineEditableTextBox* MLETB_User_Input;

	UPROPERTY(meta = (BindWidget, AllowPrivateAccess = "true"), VisibleAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	class UImage* I_Response;

	UPROPERTY(meta = (AllowPrivateAccess = "true"), EditAnywhere, BlueprintReadOnly, Category="CreateImageWidget")
	EImageSize ImageSize = EImageSize::EIS_1024;

	UFUNCTION(Category="CreateImageWidget")
	void OnUserInputChanged(const FText& Text);
	
	UFUNCTION(Category="CreateImageWidget")
	void OnSendInput();
	
	UFUNCTION(Category="CreateImageWidget")
	void OnImageRequestCompleteURL(FCreateImageResponseURL Response, FString JSONString, FString Error);

	UFUNCTION(Category="CreateImageWidget")
	void OnImageRequestComplete(UTexture2D* Texture2D);
};
