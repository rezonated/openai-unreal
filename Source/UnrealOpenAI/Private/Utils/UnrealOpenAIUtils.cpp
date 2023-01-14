// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/UnrealOpenAIUtils.h"

#include "Developer/DesktopPlatform/Public/DesktopPlatformModule.h"
#include "Utils/Utils.h"

TArray<uint8> UUnrealOpenAIUtils::OpenFileDialog()
{
	const auto DesktopPlatform = FDesktopPlatformModule::Get();

	if(!DesktopPlatform) return TArray<uint8>();

	TArray<FString> FilePaths;

	if(const auto FileDialog = DesktopPlatform->OpenFileDialog(
		nullptr,
		TEXT("Open File"),
		TEXT(""),
		TEXT(""),
		TEXT("PNG Files (*.png)|*.png"),
		EFileDialogFlags::None,
		FilePaths
	); !FileDialog) return TArray<uint8>();

	const FString FilePath = FilePaths[0];
	if( !FPaths::FileExists(FilePath)) return TArray<uint8>();

	TArray<uint8> FileData;
	if(!FFileHelper::LoadFileToArray(FileData, *FilePath)) return TArray<uint8>();

	return FileData;
}
