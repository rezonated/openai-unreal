// Created, maintained by Vanan A. - rezonated @ github.com


#include "Utils/UnrealOpenAIUtils.h"

#include "Core/Public/Misc/FileHelper.h"
#include "HttpModule.h"
#include "IImageWrapper.h"
#include "IImageWrapperModule.h"
#include "DataTypes/CommonDataTypes.h"
#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Utils/Utils.h"

bool UUnrealOpenAIUtils::OpenLoadImageDialog(FString DialogTitle, int32 SizeLimitInMB, FFileToLoad& OutFileData)
{
	OutFileData = FFileToLoad();
	
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
	if(!FPaths::FileExists(FilePath)) return false;

	TArray<uint8> FileData;
	if(!FFileHelper::LoadFileToArray(FileData, *FilePath)) return false;
	
	if (SizeLimitInMB > 0 && FileData.Num() > SizeLimitInMB * 1024 * 1024)
	{
		PrintDebugLogAndOnScreen("File size is too big. Max size is " + FString::FromInt(SizeLimitInMB) + " MB", 5, FColor::Red);
		return false;
	}

	OutFileData.FileData = FileData;
	OutFileData.FileName = FPaths::GetCleanFilename(FilePath);
	OutFileData.FileExtension = FPaths::GetExtension(FilePath);
	
	return true;
}

bool UUnrealOpenAIUtils::OpenLoadFileDialog(FString DialogTitle, FString FileExtension,  int32 SizeLimitInMB, FFileToLoad& OutFileData)
{
	OutFileData = FFileToLoad();
	
	const auto DesktopPlatform = FDesktopPlatformModule::Get();

	if(!DesktopPlatform) return false;

	TArray<FString> FilePaths;


	if (FileExtension.IsEmpty())
	{
		FileExtension = TEXT("All Files (*.*)|*.*");
	}
	else
	{
		FileExtension = FString::Printf(TEXT("%s Files (*.%s)|*.%s"), *FileExtension, *FileExtension, *FileExtension);
	}

	if(const auto FileDialog = DesktopPlatform->OpenFileDialog(
		nullptr,
		DialogTitle,
		TEXT(""),
		TEXT(""),
		*FileExtension,
		EFileDialogFlags::None,
		FilePaths
	); !FileDialog) return false;

	const FString FilePath = FilePaths[0];
	if(!FPaths::FileExists(FilePath)) return false;

	TArray<uint8> FileData;
	if(!FFileHelper::LoadFileToArray(FileData, *FilePath)) return false;
	
	if (SizeLimitInMB > 0 && FileData.Num() > SizeLimitInMB * 1024 * 1024)
	{
		PrintDebugLogAndOnScreen("File size is too big. Max size is " + FString::FromInt(SizeLimitInMB) + " MB", 5, FColor::Red);
		return false;
	}

	OutFileData.FileData = FileData;
	OutFileData.FileName = FPaths::GetCleanFilename(FilePath);
	OutFileData.FileExtension = FPaths::GetExtension(FilePath);
	
	return true;
}

bool UUnrealOpenAIUtils::OpenSaveFileDialog(FString DialogTitle, TArray<uint8> FileData, FString FileName,
                                            FString FileExtension, FString& OutFilePath)
{
	OutFilePath = FString();
	
	const auto DesktopPlatform = FDesktopPlatformModule::Get();

	if(!DesktopPlatform) return false;

	TArray<FString> FilePaths;

	if(const auto FileDialog = DesktopPlatform->SaveFileDialog(
		nullptr,
		DialogTitle,
		TEXT(""),
		*FileName,
		FString::Printf(TEXT(" (*.%s)|*.%s"), *FileExtension, *FileExtension),
		EFileDialogFlags::None,
		FilePaths
	); !FileDialog) return false;

	const FString FilePath = FilePaths[0];
	if(!FFileHelper::SaveArrayToFile(FileData, *FilePath)) return false;

	OutFilePath = FilePath;
	
	return true;
}

bool UUnrealOpenAIUtils::ConvertBytesToTexture2D(TArray<uint8> FileData, UTexture2D*& OutTexture)
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

bool UUnrealOpenAIUtils::ConvertBase64ToTexture2D(FString Base64Data, UTexture2D*& OutTexture)
{
	OutTexture = nullptr;
	if(Base64Data.IsEmpty()) return false;

	TArray<uint8> FileData;
	if(!FBase64::Decode(Base64Data, FileData)) return false;

	return ConvertBytesToTexture2D(FileData, OutTexture);
}

void UUnrealOpenAIUtilsGetImageFromURL::OnProcessRequestComplete(
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest,
	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful)
{
	if(!bSuccessful)
	{
		OnFailure.Broadcast(nullptr);
		return;
	}

	if (const TArray<uint8> ResponseData = HttpResponse->GetContent(); UUnrealOpenAIUtils::ConvertBytesToTexture2D(ResponseData, Texture2D))
	{
		OnSuccess.Broadcast(Texture2D);
	}
	else
	{
		OnFailure.Broadcast(nullptr);
	}
}

UUnrealOpenAIUtilsDownloadFileFromURL* UUnrealOpenAIUtilsDownloadFileFromURL::DownloadFileFromURL(
	UObject* WorldContextObject, FString URL)
{
	UUnrealOpenAIUtilsDownloadFileFromURL* Proxy = NewObject<UUnrealOpenAIUtilsDownloadFileFromURL>();
	Proxy->WorldContextObject = WorldContextObject;
	Proxy->URL = URL;
	return Proxy;
}

void UUnrealOpenAIUtilsDownloadFileFromURL::OnProcessRequestComplete(
	TSharedPtr<IHttpRequest, ESPMode::ThreadSafe> HttpRequest,
	TSharedPtr<IHttpResponse, ESPMode::ThreadSafe> HttpResponse, bool bSuccessful)
{
	FileData = FFileToLoad();
	if(!bSuccessful)
	{
		OnFailure.Broadcast(FileData);
		return;
	}
	
	const TArray<uint8> ResponseData = HttpResponse->GetContent();
	if(ResponseData.Num() == 0)
	{
		OnFailure.Broadcast(FileData);
		return;
	}

	FileData.FileData = ResponseData;
	FileData.FileName = FPaths::GetCleanFilename(URL);
	FileData.FileExtension = FPaths::GetExtension(URL);
	
	OnSuccess.Broadcast(FileData);
}

void UUnrealOpenAIUtilsDownloadFileFromURL::Activate()
{
	Super::Activate();

	if(!WorldContextObject)
	{
		PrintDebugLogAndOnScreen("WorldContextObject is null", true);
		OnFailure.Broadcast(FFileToLoad());
		return;
	}

	const auto HTTP = &FHttpModule::Get();

	if (!HTTP)
	{
		OnFailure.Broadcast(FFileToLoad());
		return;
	}
	const auto HTTPRequest = HTTP->CreateRequest();

	HTTPRequest->SetURL(URL);
	HTTPRequest->SetVerb("GET");
	HTTPRequest->OnProcessRequestComplete().BindUObject(this, &UUnrealOpenAIUtilsDownloadFileFromURL::OnProcessRequestComplete);


	if (!HTTPRequest->ProcessRequest())
	{
		OnFailure.Broadcast(FFileToLoad());
	}
}

UUnrealOpenAIUtilsGetImageFromURL* UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(UObject* WorldContextObject,FString URL)
{
	UUnrealOpenAIUtilsGetImageFromURL* Proxy = NewObject<UUnrealOpenAIUtilsGetImageFromURL>();
	Proxy->URL = URL;
	Proxy->WorldContextObject = WorldContextObject;
	return Proxy;
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