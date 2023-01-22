// Created, maintained by Vanan A. - rezonated @ github.com

#include "Tests/Actors/FunctionalTestPawn.h"

#include "Enums/CompletionEnums.h"
#include "Proxies/CompletionProxies.h"
#include "Proxies/EditsProxies.h"
#include "Proxies/EmbeddingsProxies.h"
#include "Proxies/FilesProxies.h"
#include "Proxies/ImageProxies.h"
#include "Proxies/ModerationProxies.h"
#include "Tests/FunctionalTests/CompletionFunctionalTest.h"
#include "Tests/FunctionalTests/EditsFunctionalTest.h"
#include "Tests/FunctionalTests/EmbeddingsFunctionalTest.h"
#include "Utils/UnrealOpenAIUtils.h"
#include "Core/Public/Misc/FileHelper.h"
#include "Runtime/Core/Public/Misc/Paths.h"


AFunctionalTestPawn::AFunctionalTestPawn()
{
	PrimaryActorTick.bCanEverTick = false;
}


void AFunctionalTestPawn::StartCompletionsTest(FString Prompt)
{
	if (!CompletionsFunctionalTest)
		return;

	if (Prompt.IsEmpty() || Prompt.Len() <= 0 || Prompt == TEXT(""))
	{
		CompletionsFunctionalTest->FailTest(TEXT("Prompt is empty"));
	}
	
	const auto Proxy = UCreateCompletionRequestProxy::CreateCompletion(this, Prompt, ECompletionModel::ECM_Davinci);

	if (!Proxy)
	{
		CompletionsFunctionalTest->FailTest(TEXT("Failed to create completion request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCompletionSuccess);

	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCompletionFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCompletionSuccess(FCreateCompletionResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		CompletionsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		CompletionsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (Response.choices[0].text.IsEmpty())
	{
		CompletionsFunctionalTest->FailTest(TEXT("No response text returned"));
		return;
	}

	CompletionsFunctionalTest->PassTest(FString::Printf(TEXT("Response text returned %s"), *Response.choices[0].text));
}

void AFunctionalTestPawn::OnCompletionFailure(FCreateCompletionResponse Response, FString JSONString, FString Error)
{
	CompletionsFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCompletionFailure"));
}

void AFunctionalTestPawn::StartEditsTest(FString Input, FString Instruction)
{
	if (!EditsFunctionalTest)
		return;

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		EditsFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	if (Instruction.IsEmpty() || Instruction.Len() <= 0 || Instruction == TEXT(""))
	{
		EditsFunctionalTest->FailTest(TEXT("Instruction is empty"));
		return;
	}

	const auto Proxy = UCreateEditsRequestProxy::CreateEdits(this, Input, Instruction);

	if (!Proxy)
	{
		EditsFunctionalTest->FailTest(TEXT("Failed to create edits request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnEditsSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnEditsFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnEditsSuccess(FCreateEditsResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		EditsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		EditsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	if (Response.choices[0].text.IsEmpty())
	{
		EditsFunctionalTest->FailTest(TEXT("No response text returned"));
		return;
	}
	
	EditsFunctionalTest->PassTest(FString::Printf(TEXT("Response text returned %s"), *Response.choices[0].text));
}

void AFunctionalTestPawn::OnEditsFailure(FCreateEditsResponse Response, FString JSONString, FString Error)
{
	EditsFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnEditsFailure"));
}

void AFunctionalTestPawn::StartEmbeddingsTest(FString Input)
{
	if (!EmbeddingsFunctionalTest)
	{
		return;
	}

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		EmbeddingsFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	const auto Proxy = UCreateEmbeddingsRequestProxy::CreateEmbeddings(this, Input);

	if (!Proxy)
	{
		EmbeddingsFunctionalTest->FailTest(TEXT("Failed to create embeddings request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnEmbeddingsSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnEmbeddingsFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnEmbeddingsSuccess(FCreateEmbeddingsResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		EmbeddingsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		EmbeddingsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.data.Num() < 0)
	{
		EmbeddingsFunctionalTest->FailTest(TEXT("No response data returned"));
		return;
	}
	
	EmbeddingsFunctionalTest->PassTest(FString::Printf(TEXT("Response data returned with length of %d"), Response.data.Num()));
}

void AFunctionalTestPawn::OnEmbeddingsFailure(FCreateEmbeddingsResponse Response, FString JSONString, FString Error)
{
	EmbeddingsFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnEmbeddingsFailure"));
}

void AFunctionalTestPawn::StartModerationsTest(FString Input)
{
	if (!ModerationsFunctionalTest)
	{
		return;
	}

	if (Input.IsEmpty() || Input.Len() <= 0 || Input == TEXT(""))
	{
		ModerationsFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	const auto Proxy = UCreateModerationRequestProxy::CreateModerationRequest(this, Input, EModerationModels::EMM_Stable);

	if (!Proxy)
	{
		ModerationsFunctionalTest->FailTest(TEXT("Failed to create moderation request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnModerationSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnModerationFailure);

	Proxy->Activate();	 
}

void AFunctionalTestPawn::OnModerationSuccess(FCreateModerationResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		ModerationsFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ModerationsFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (!Response.results[0].flagged)
	{
		ModerationsFunctionalTest->FailTest(TEXT("Response is not flagged as expected"));
		return;
	}
	
	ModerationsFunctionalTest->PassTest(TEXT("Response is flagged correctly"));
}

void AFunctionalTestPawn::OnModerationFailure(FCreateModerationResponse Response, FString JSONString, FString Error)
{
	 ModerationsFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnModerationFailure"));
}

void AFunctionalTestPawn::StartCreateFileTest(const FString TestFilePath)
{
	if (!FilesFunctionalTest)
	{
		return;
	}

	if (TestFilePath.IsEmpty() || TestFilePath.Len() <= 0 || TestFilePath == TEXT(""))
	{
		FilesFunctionalTest->FailTest(TEXT("Input is empty"));
		return;
	}

	FFileToLoad FileToLoad;
	TArray<uint8> FileResult;
	 FFileHelper::LoadFileToArray(FileResult, *TestFilePath);
	FileToLoad.FileData = FileResult;
	FileToLoad.FileName = FPaths::GetCleanFilename(TestFilePath);
	FileToLoad.FileExtension = FPaths::GetExtension(TestFilePath);

	if (FileResult.Num() <= 0)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to load file"));
		return;
	}

	if (FileToLoad.FileName != TEXT("training.jsonl"))
	{
		FilesFunctionalTest->FailTest(TEXT("File name is not correct, should be test.jsonl; check if the test.jsonl is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (FileToLoad.FileExtension != TEXT("jsonl"))
	{
		FilesFunctionalTest->FailTest(TEXT("File extension is not correct, should be jsonl; check if the test.jsonl is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	const auto Proxy = UUploadFileRequestProxy::UploadFileRequest(this, FileToLoad, TEXT("fine-tune"));

	if (!Proxy)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to create upload files request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateFileSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateFileFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateFileSuccess(FFileResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.id.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Response id is empty"));
		return;
	}

	FilesFunctionalTest->OnFileUploadTestComplete();
}

void AFunctionalTestPawn::OnCreateFileFailure(FFileResponse Response, FString JSONString, FString Error)
{
	FilesFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateFileFailure"));
}

void AFunctionalTestPawn::StartListFilesTest()
{
	if (!FilesFunctionalTest)
	{
		return;
	}

	const auto Proxy = UListFilesRequestProxy::ListFilesRequest(this);

	if (!Proxy)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to create list files request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnListFileSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnListFileFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnListFileSuccess(FListFilesResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.data.Num() <= 0)
	{
		FilesFunctionalTest->FailTest(TEXT("No files listed"));
		return;
	}
	
	FilesFunctionalTest->OnListFilesTestComplete(Response.data[0].id);
}

void AFunctionalTestPawn::OnListFileFailure(FListFilesResponse Response, FString JSONString, FString Error)
{
	FilesFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnListFileFailure"));
}

void AFunctionalTestPawn::StartRetrieveFileTest(FString ID)
{
	if (!FilesFunctionalTest)
	{
		return;
	}

	if (ID.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("ID is empty"));
		return;
	}

	FileID = ID;

	const auto Proxy = URetrieveFileRequestProxy::RetrieveFileRequest(this, ID);

	if (!Proxy)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to create retrieve file request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnRetrieveFileSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnRetrieveFileFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnRetrieveFileSuccess(FFileResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.id.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Response id is empty"));
		return;
	}

	if (!Response.id.Equals(FileID))
	{
		FilesFunctionalTest->FailTest(TEXT("Response id is not the same as the requested id"));
		return;
	}
	
	FilesFunctionalTest->OnRetrieveFileTestComplete(FileID);
}

void AFunctionalTestPawn::OnRetrieveFileFailure(FFileResponse Response, FString JSONString, FString Error)
{
	FilesFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnRetrieveFileFailure"));
}

void AFunctionalTestPawn::StartDeleteFileTest(FString ID)
{
	if (!FilesFunctionalTest)
	{
		return;
	}

	if (ID.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("ID is empty"));
		return;
	}

	FileID = ID;

	const auto Proxy = UDeleteFileRequestProxy::DeleteFileRequest(this, ID);

	if (!Proxy)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to create delete file request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnDeleteFileSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnDeleteFileFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnDeleteFileSuccess(FDeleteResponse Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}
	
	if (Response.id.IsEmpty())
	{
		FilesFunctionalTest->FailTest(TEXT("Response id is empty"));
		return;
	}

	if (!Response.id.Equals(FileID))
	{
		FilesFunctionalTest->FailTest(TEXT("Response id is not the same as the requested id"));
		return;
	}
	
	FilesFunctionalTest->OnDeleteFileTestComplete();
}

void AFunctionalTestPawn::OnDeleteFileFailure(FDeleteResponse Response, FString JSONString, FString Error)
{
	FilesFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnDeleteFileFailure"));
}

void AFunctionalTestPawn::StartCreateImageURLTest(FString Prompt)
{
	if (!ImageURLFunctionalTest)
	{
		return;
	}

	if (Prompt.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Prompt is empty"));
		return;
	}

	const auto Proxy = UCreateImageRequestURL::CreateImageURL(this, Prompt, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to create create image url request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageURLSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageURLFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageURLSuccess(FCreateImageResponseURL Response, FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (Response.data.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}
	
	if (Response.data[0].url.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response url is empty"));
		return;
	}

	const auto GetImageFromURLProxy = UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(this, Response.data[0].url);

	if (!GetImageFromURLProxy)
	{
		FilesFunctionalTest->FailTest(TEXT("Failed to create get image from url request proxy"));
		return;
	}

	GetImageFromURLProxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageFromURLSuccess);

	GetImageFromURLProxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageFromURLFailure);

	GetImageFromURLProxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageURLFailure(FCreateImageResponseURL Response, FString JSONString, FString Error)
{
	ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageURLFailure"));
}

void AFunctionalTestPawn::OnGetCreateImageFromURLSuccess(UTexture2D* Texture2D)
{
	if (!Texture2D)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Texture2D is null"));
		return;
	}

	ImageURLFunctionalTest->OnCreateImageURLTestComplete();
}

void AFunctionalTestPawn::OnGetCreateImageFromURLFailure(UTexture2D* Texture2D)
{
	ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnGetCreateImageFromURLFailure"));
}

void AFunctionalTestPawn::StartCreateImageEditURLTest(FString ImagePath, FString MaskPath, FString Prompt)
{
	if (!ImageURLFunctionalTest)
	{
		return;
	}

	if (ImagePath.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Image path is empty"));
		return;
	}

	if (MaskPath.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Mask path is empty"));
		return;
	}

	if (Prompt.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Prompt is empty"));
	}

	FFileToLoad ImageFile;
	TArray<uint8> ImageResult;
	FFileHelper::LoadFileToArray(ImageResult, *ImagePath);
	ImageFile.FileData = ImageResult;
	ImageFile.FileName = FPaths::GetCleanFilename(ImagePath);
	ImageFile.FileExtension = FPaths::GetExtension(ImagePath);

	if (ImageResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load image file"));
		return;
	}

	if (ImageFile.FileName != TEXT("pool_empty.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_empty.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (ImageFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	FFileToLoad MaskFile;
	TArray<uint8> MaskResult;
	FFileHelper::LoadFileToArray(MaskResult, *MaskPath);
	MaskFile.FileData = MaskResult;
	MaskFile.FileName = FPaths::GetCleanFilename(MaskPath);
	MaskFile.FileExtension = FPaths::GetExtension(MaskPath);

	if (MaskResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load mask file"));
		return;
	}

	if (MaskFile.FileName != TEXT("pool_mask.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_mask.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (MaskFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_mask.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	const auto Proxy = UCreateImageEditRequestURL::CreateImageEditURL(this, ImageFile, MaskFile, Prompt, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to create create image edit url request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditURLSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditURLFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditURLSuccess(FCreateImageResponseURL ResponseURL, FString JSONString,
	FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (ResponseURL.data.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}

	if (ResponseURL.data[0].url.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response url is empty"));
		return;
	}

	const auto GetImageFromURLProxy = UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(this, ResponseURL.data[0].url);

	if (!GetImageFromURLProxy)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to create get image from url request proxy"));
		return;
	}

	GetImageFromURLProxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageEditFromURLSuccess);

	GetImageFromURLProxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageEditFromURLFailure);

	GetImageFromURLProxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditURLFailure(FCreateImageResponseURL ResponseURL, FString JSONString,
	FString Error)
{
	 ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageEditURLFailure"));
}

void AFunctionalTestPawn::OnGetCreateImageEditFromURLSuccess(UTexture2D* Texture2D)
{
 	if (!Texture2D)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Texture2D is null"));
		return;
	}

	ImageURLFunctionalTest->OnCreateImageEditURLTestComplete();	
}

void AFunctionalTestPawn::OnGetCreateImageEditFromURLFailure(UTexture2D* Texture2D)
{
	ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnGetCreateImageEditFromURLFailure"));
}

void AFunctionalTestPawn::StartCreateImageEditVariationURLTest(FString ImagePath)
{
	if (!ImageURLFunctionalTest)
	{
		return;
	}

	if (ImagePath.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Image path is empty"));
		return;
	}

	FFileToLoad ImageFile;
	TArray<uint8> ImageResult;
	FFileHelper::LoadFileToArray(ImageResult, *ImagePath);
	ImageFile.FileData = ImageResult;
	ImageFile.FileName = FPaths::GetCleanFilename(ImagePath);
	ImageFile.FileExtension = FPaths::GetExtension(ImagePath);

	if (ImageResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load image file"));
		return;
	}

	if (ImageFile.FileName != TEXT("pool_empty.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_empty.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (ImageFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	const auto Proxy = UCreateImageVariationRequestURL::CreateImageVariationURL(this, ImageFile, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to create create image edit variation url request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditVariationURLSuccess);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditVariationURLFailure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditVariationURLSuccess(FCreateImageResponseURL ResponseURL, FString JSONString,
	FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (ResponseURL.data.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}

	if (ResponseURL.data[0].url.IsEmpty())
	{
		ImageURLFunctionalTest->FailTest(TEXT("Response url is empty"));
		return;
	}

	const auto GetImageFromURLProxy = UUnrealOpenAIUtilsGetImageFromURL::GetImageFromURL(this, ResponseURL.data[0].url);

	if (!GetImageFromURLProxy)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to create get image from url request proxy"));
		return;
	}

	GetImageFromURLProxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageEditVariationFromURLSuccess);

	GetImageFromURLProxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnGetCreateImageEditVariationFromURLFailure);

	GetImageFromURLProxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditVariationURLFailure(FCreateImageResponseURL ResponseURL, FString JSONString,
	FString Error)
{
	ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageEditVariationURLFailure"));
}

void AFunctionalTestPawn::OnGetCreateImageEditVariationFromURLSuccess(UTexture2D* Texture2D)
{
	if (!Texture2D)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Texture2D is null"));
		return;
	}

	ImageURLFunctionalTest->OnCreateImageEditVariationURLTestComplete();
}

void AFunctionalTestPawn::OnGetCreateImageEditVariationFromURLFailure(UTexture2D* Texture2D)
{
	ImageURLFunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnGetCreateImageEditVariationFromURLFailure"));
}

void AFunctionalTestPawn::StartCreateImageBase64Test(FString Prompt)
{
	if (!ImageBase64FunctionalTest)
	{
		return;
	}

	if (Prompt.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Prompt is empty"));
		return;
	}

	const auto Proxy = UCreateImageRequestBase64JSON::CreateImageBase64JSON(this, Prompt, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to create create image base64 request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageBase64Success);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageBase64Failure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageBase64Success(FCreateImageResponseBase64JSON Response, FString JSONString,
	FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (Response.data.Num() <= 0)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}

	if (Response.data[0].b64_json.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response base64 is empty"));
		return;
	}

	UTexture2D* OutTexture;
	if (!UUnrealOpenAIUtils::ConvertBase64ToTexture2D(Response.data[0].b64_json, OutTexture))
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to convert base64 to texture2d"));
		return;
	}

	if (!OutTexture)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("OutTexture is null"));
		return;
	}

	ImageBase64FunctionalTest->OnCreateImageBase64TestComplete();
}

void AFunctionalTestPawn::OnCreateImageBase64Failure(FCreateImageResponseBase64JSON Response, FString JSONString,
	FString Error)
{
	ImageBase64FunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageBase64Failure"));
}

void AFunctionalTestPawn::StartCreateImageEditBase64Test(FString ImagePath, FString MaskPath, const FString Prompt)
{
	if (!ImageBase64FunctionalTest)
	{
		return;
	}

	if (Prompt.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Prompt is empty"));
		return;
	}

	FFileToLoad ImageFile;
	TArray<uint8> ImageResult;
	FFileHelper::LoadFileToArray(ImageResult, *ImagePath);
	ImageFile.FileData = ImageResult;
	ImageFile.FileName = FPaths::GetCleanFilename(ImagePath);
	ImageFile.FileExtension = FPaths::GetExtension(ImagePath);

	if (ImageResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load image file"));
		return;
	}

	if (ImageFile.FileName != TEXT("pool_empty.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_empty.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (ImageFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	FFileToLoad MaskFile;
	TArray<uint8> MaskResult;
	FFileHelper::LoadFileToArray(MaskResult, *MaskPath);
	MaskFile.FileData = MaskResult;
	MaskFile.FileName = FPaths::GetCleanFilename(MaskPath);
	MaskFile.FileExtension = FPaths::GetExtension(MaskPath);

	if (MaskResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load mask file"));
		return;
	}

	if (MaskFile.FileName != TEXT("pool_mask.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_mask.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (MaskFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_mask.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	const auto Proxy = UCreateImageEditRequestBase64JSON::CreateImageEditJSON(this, ImageFile, MaskFile, Prompt, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to create create image edit base64 request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditBase64Success);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditBase64Failure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditBase64Success(FCreateImageResponseBase64JSON Response,
	FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (Response.data.Num() <= 0)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}

	if (Response.data[0].b64_json.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response base64 is empty"));
		return;
	}

	UTexture2D* OutTexture;
	if (!UUnrealOpenAIUtils::ConvertBase64ToTexture2D(Response.data[0].b64_json, OutTexture))
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to convert base64 to texture2d"));
		return;
	}

	if (!OutTexture)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("OutTexture is null"));
		return;
	}

	ImageBase64FunctionalTest->OnCreateImageEditBase64TestComplete();
}

void AFunctionalTestPawn::OnCreateImageEditBase64Failure(FCreateImageResponseBase64JSON ResponseBase64JSON,
	FString JSONString, FString Error)
{
	ImageBase64FunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageEditBase64Failure"));
}

void AFunctionalTestPawn::StartCreateImageEditVariationBase64Test(FString ImagePath)
{
	if (!ImageBase64FunctionalTest)
	{
		return;
	}

	FFileToLoad ImageFile;
	TArray<uint8> ImageResult;
	FFileHelper::LoadFileToArray(ImageResult, *ImagePath);
	ImageFile.FileData = ImageResult;
	ImageFile.FileName = FPaths::GetCleanFilename(ImagePath);
	ImageFile.FileExtension = FPaths::GetExtension(ImagePath);

	if (ImageResult.Num() <= 0)
	{
		ImageURLFunctionalTest->FailTest(TEXT("Failed to load image file"));
		return;
	}

	if (ImageFile.FileName != TEXT("pool_empty.png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File name is not correct, should be pool_empty.png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	if (ImageFile.FileExtension != TEXT("png"))
	{
		ImageURLFunctionalTest->FailTest(TEXT("File extension is not correct, should be png; check if the pool_empty.png is present inside Plugins/UnrealOpenAI/Content/Test/"));
		return;
	}

	const auto Proxy = UCreateImageVariationRequestBase64JSON::CreateImageVariationJSON(this, ImageFile, EImageSize::EIS_256);

	if (!Proxy)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to create create image edit variation base64 request proxy"));
		return;
	}

	Proxy->OnSuccess.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditVariationBase64Success);
	Proxy->OnFailure.AddDynamic(this, &AFunctionalTestPawn::OnCreateImageEditVariationBase64Failure);

	Proxy->Activate();
}

void AFunctionalTestPawn::OnCreateImageEditVariationBase64Success(FCreateImageResponseBase64JSON ResponseBase64JSON,
	FString JSONString, FString Error)
{
	if (JSONString.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("No JSON String returned"));
		return;
	}

	if (!Error.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Error returned"));
		return;
	}

	if (ResponseBase64JSON.data.Num() <= 0)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response data is empty"));
		return;
	}

	if (ResponseBase64JSON.data[0].b64_json.IsEmpty())
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Response base64 is empty"));
		return;
	}

	UTexture2D* OutTexture;
	if (!UUnrealOpenAIUtils::ConvertBase64ToTexture2D(ResponseBase64JSON.data[0].b64_json, OutTexture))
	{
		ImageBase64FunctionalTest->FailTest(TEXT("Failed to convert base64 to texture2d"));
		return;
	}

	if (!OutTexture)
	{
		ImageBase64FunctionalTest->FailTest(TEXT("OutTexture is null"));
		return;
	}

	ImageBase64FunctionalTest->OnCreateImageEditVariationBase64TestComplete();
}

void AFunctionalTestPawn::OnCreateImageEditVariationBase64Failure(FCreateImageResponseBase64JSON ResponseBase64JSON, FString JSONString, FString Error)
{
	ImageBase64FunctionalTest->FailTest(TEXT("Should not fire failure delegate - OnCreateImageEditVariationBase64Failure"));
}
