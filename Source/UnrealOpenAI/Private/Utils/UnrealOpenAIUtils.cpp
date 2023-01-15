// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/UnrealOpenAIUtils.h"

#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

bool UUnrealOpenAIUtils::OpenImageDialog(FString DialogTitle, TArray<uint8>& OutFileData)
{
	OutFileData = TArray<uint8>();
	const auto DesktopPlatform = FDesktopPlatformModule::Get();

	if(!DesktopPlatform) return false;

	TArray<FString> FilePaths;

	if(const auto FileDialog = DesktopPlatform->OpenFileDialog(
		nullptr,
		DialogTitle,
		TEXT(""),
		TEXT(""),
		TEXT("PNG Files (*.png)|*.png"),
		EFileDialogFlags::None,
		FilePaths
	); !FileDialog) return false;

	const FString FilePath = FilePaths[0];
	if( !FPaths::FileExists(FilePath)) return false;

	TArray<uint8> FileData;
	if(!FFileHelper::LoadFileToArray(FileData, *FilePath)) return false;

	OutFileData = FileData;
	return true;
}

bool UUnrealOpenAIUtils::ConvertToTexture2D(TArray<uint8> FileData, UTexture2D*& OutTexture)
{
	OutTexture = nullptr;
	if(FileData.Num() == 0) return false;

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	if(!ImageWrapper.IsValid()) return false;

	if(!ImageWrapper->SetCompressed(FileData.GetData(), FileData.Num())) return false;


	TArray64<uint8> RawData;
	if(!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData)) return false;

	const int32 Width = ImageWrapper->GetWidth();
	const int32 Height = ImageWrapper->GetHeight();

	OutTexture = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
	if(!OutTexture) return false;

	void* TextureData = OutTexture->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData,
	                RawData.GetData(), RawData.Num());
	OutTexture->GetPlatformData()->Mips[0].BulkData.Unlock();

	OutTexture->UpdateResource();
	return true;
}

void UUnrealOpenAIUtilsGetImageFromURL::OnProcessRequestComplete(
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest,
	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bArg)
{
	if(!bArg)
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	const TArray<uint8> ResponseData = HttpResponse->GetContent();
	if(ResponseData.Num() == 0)
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	IImageWrapperModule& ImageWrapperModule = FModuleManager::LoadModuleChecked<IImageWrapperModule>(FName("ImageWrapper"));
	const TSharedPtr<IImageWrapper> ImageWrapper = ImageWrapperModule.CreateImageWrapper(EImageFormat::PNG);
	if(!ImageWrapper.IsValid())
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	if(!ImageWrapper->SetCompressed(ResponseData.GetData(), ResponseData.Num()))
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	TArray64<uint8> RawData;
	if(!ImageWrapper->GetRaw(ERGBFormat::BGRA, 8, RawData))
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	const int32 Width = ImageWrapper->GetWidth();
	const int32 Height = ImageWrapper->GetHeight();

	Texture2D = UTexture2D::CreateTransient(Width, Height, PF_B8G8R8A8);
	if(!Texture2D)
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	void* TextureData = Texture2D->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(TextureData,
					RawData.GetData(), RawData.Num());
	Texture2D->GetPlatformData()->Mips[0].BulkData.Unlock();

	Texture2D->UpdateResource();

	OnSuccess.Broadcast(Texture2D);
}

void UUnrealOpenAIUtilsGetImageFromURL::Activate()
{
	Super::Activate();

	if (!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null");
		OnFailure.Broadcast(nullptr);
		return;
	}

	const auto HTTP = &FHttpModule::Get();

	if (!HTTP)
	{
		OnFailure.Broadcast(nullptr);
		return;
	}
	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->SetURL(URL);
	HTTPRequest->SetVerb("GET");

	HTTPRequest->OnProcessRequestComplete().BindUObject(this, &UUnrealOpenAIUtilsGetImageFromURL::OnProcessRequestComplete);

	if (!HTTPRequest->ProcessRequest())
	{
		OnFailure.Broadcast(nullptr);
	}
}

UUnrealOpenAIUtilsGetImageFromURL* UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(UObject* WorldContextObject,
	FString URL)
{
	UUnrealOpenAIUtilsGetImageFromURL* Proxy = NewObject<UUnrealOpenAIUtilsGetImageFromURL>();
	Proxy->URL = URL;
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
}
