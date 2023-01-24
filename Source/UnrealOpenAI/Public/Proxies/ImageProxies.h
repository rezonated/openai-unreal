// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "DataTypes/CommonDataTypes.h"
#include "DataTypes/ImageDataTypes.h"
#include "Net/OnlineBlueprintCallProxyBase.h"
#include "ImageProxies.generated.h"

#pragma region Create Image Proxies

// Delegate for the create image URL request proxy, will return the response in
// FCreateImageResponseURL struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageRequestCallbackSignatureURL, FCreateImageResponseURL, Response, FString, JSONString, FString, Error);

// Class to handle the create image URL request proxy, exposes the OnSuccess and OnFailure
// and executes asynchronously due to it being based on the OnlineBlueprintCallProxyBase.
// Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image URL request is successful, will return the response in
	 * FCreateImageResponseURL struct, a valid JSON string response and an empty error
	 * string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnSuccess;

	/**
	 * Fired when the create image URL request fails, will return an empty
	 * FCreateImageResponseURL struct, JSON string error response, and an error string for
	 * error message 
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureURL OnFailure;

	/**
	 * Implementation of the create image URL request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/images/create
	 *
	 * Creates an image given a prompt.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Prompt A text description of the desired image(s).
	 * The maximum length is 1000 characters.
	 * @param ImageSize The size of the generated images.
	 * Must be one of 256x256, 512x512, or 1024x1024.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageRequestURL* CreateImageURL(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	/**
	 * Activates the create image URL request proxy, call this function in C++ to execute
	 * the request 
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's prompt
	 */
	FString Prompt;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;
};

// Delegate for the create image base64 JSON request proxy, will return the response in
// FCreateImageResponseBase64JSON struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, Response, FString, JSONString, FString, Error);

// Class to handle the create image base64 JSON request proxy, exposes the OnSuccess and
// OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image base64 JSON request is successful, will return the
	 * response in FCreateImageResponseBase64JSON struct, a valid JSON string response and
	 * an empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnSuccess;

	/**
	 * Fired when the create image base64 JSON request fails, will return an empty
	 * FCreateImageResponseBase64JSON struct, JSON string error response, and an error
	 * string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageRequestCallbackSignatureBase64JSON OnFailure;

	/**
	 * Implementation of the create image base64 JSON request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/images/create
	 *
	 * Creates an image given a prompt.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param Prompt A text description of the desired image(s).
	 * @param ImageSize The size of the generated images.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageRequestBase64JSON* CreateImageBase64JSON(UObject* WorldContextObject, FString Prompt, EImageSize ImageSize);

	/**
	 * Activates the create image base64 JSON request proxy, call this function in C++ to
	 * execute the request 
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's prompt
	 */
	FString Prompt;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;	
};

#pragma endregion

#pragma region Create Image Edit Proxies

// Delegate for the create image edit url request proxy, will return the response in
// FCreateImageResponseURL struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageEditRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString, FString, Error);

// Class to handle the create image edit url request proxy, exposes the OnSuccess and
// OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageEditRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image edit URL request is successful, will return the
	 * response in FCreateImageResponseURL struct, a valid JSON string response and an
	 * empty error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnSuccess;

	/**
	 * Fired when the create image edit URL request fails, will return an empty
	 * FCreateImageResponseURL struct, JSON string error response, and an error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureURL OnFailure;

	/**
	 * Implementation of the create image edit URL request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/images/create-edit
	 *
	 * Creates an edited or extended image given an original image and a prompt.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param ImageFile The image to edit. Can be obtained using
	 * UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and
	 * square. If mask is not provided, image must have transparency, which will be used
	 * as the mask. 
	 * @param MaskImageFile An additional image whose fully transparent areas (e.g. where alpha is zero) indicate where image should be edited. Also can be obtained using
	 * UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and have the same dimensions as image.
	 * @param Prompt A text description of the desired image(s).
	 * The maximum length is 1000 characters.
	 * @param ImageSize The size of the generated images.
	 * Must be one of 256x256, 512x512, or 1024x1024. 
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageEditRequestURL* CreateImageEditURL(UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize);

	/**
	 * Activates the create image edit URL request proxy, call this function in C++ to
	 * execute the request  
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's image file
	 */
	FFileToLoad ImageFile;

	/**
	 * Current request's mask image file
	 */
	FFileToLoad MaskImageFile;

	/**
	 * Current request's prompt
	 */
	FString Prompt;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;
};

// Delegate for the create image edit base64 JSON request proxy, will return the response
// in FCreateImageResponseBase64JSON struct, a JSON string response containing either a
// valid response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageEditRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString, FString, Error);

// Class to handle the create image edit base64 JSON request proxy, exposes the OnSuccess
// and OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageEditRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image edit base64 JSON request is successful, will return the
	 * response in FCreateImageResponseBase64JSON struct, a valid JSON string response and
	 * an empty error string 
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnSuccess;

	/**
	 * Fired when the create image edit base64 JSON request fails, will return an empty
	 * FCreateImageResponseBase64JSON struct, JSON string error response, and an error
	 * string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageEditRequestCallbackSignatureBase64JSON OnFailure;

	/**
	 * Implementation of the create image edit base64 JSON request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/images/create-edit
	 *
	 * Creates an edited or extended image given an original image and a prompt.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param ImageFile The image to edit. Can be obtained using
	 * UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and square. If mask is not provided, image must have transparency, which will be used as the mask.
	 * @param MaskImageFile An additional image whose fully transparent areas (e.g. where
	 * alpha is zero) indicate where image should be edited. Also can be obtained using
	 * UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and have the same dimensions as image.  
	 * @param Prompt A text description of the desired image(s).
	 * The maximum length is 1000 
	 * @param ImageSize The size of the generated images.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageEditRequestBase64JSON* CreateImageEditJSON(UObject* WorldContextObject, FFileToLoad ImageFile, FFileToLoad MaskImageFile, FString Prompt, EImageSize ImageSize);

	/**
	 * Activates the create image edit base64 JSON request proxy, call this function in
	 * C++ to execute the request  
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's image file
	 */
	FFileToLoad ImageFile;

	/**
	 * Current request's mask image file
	 */
	FFileToLoad MaskImageFile;

	/**
	 * Current request's prompt
	 */
	FString Prompt;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;
};

#pragma endregion

#pragma region Create Image Variation Proxies

// Delegate for the create image variation edit URL request proxy, will return the response
// in FCreateImageResponseURL struct, a JSON string response containing either a valid
// response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageVariationRequestCallbackSignatureURL, FCreateImageResponseURL, ResponseURL, FString, JSONString, FString, Error);

// Class to handle the create image variation URL request proxy, exposes the OnSuccess
// and OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageVariationRequestURL : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image variation URL request is successful, will return the
	 * response in FCreateImageResponseURL struct, a valid JSON string response and an
	 * empty error string 
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnSuccess;

	/**
	 * Fired when the create image variation URL request fails, will return an empty
	 * FCreateImageResponseURL struct, JSON string error response, and an error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureURL OnFailure;

	/**
	 * Implementation of the create image variation URL request API call as defined in:
	 * https://beta.openai.com/docs/api-reference/images/create-variation
	 *
	 * Creates a variation of a given image.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param ImageFile The image to edit. Can be obtained using UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and square.
	 * @param ImageSize The size of the generated images.
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageVariationRequestURL* CreateImageVariationURL(UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize);

	/**
	 * Activates the create image variation URL request proxy, call this function in C++
	 * to execute the request  
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's image file
	 */
	FFileToLoad ImageFile;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;
};

// Delegate for the create image variation edit base64 JSON request proxy, will return the
// response in FCreateImageResponseBase64JSON struct, a JSON string response containing
// either a valid response or error response, and an error string when the request fails
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FCreateImageVariationRequestCallbackSignatureBase64JSON, FCreateImageResponseBase64JSON, ResponseBase64JSON, FString, JSONString, FString, Error);

// Class to handle the create image variation base64 JSON request proxy, exposes the
// OnSuccess and OnFailure and executes asynchronously due to it being based on the
// OnlineBlueprintCallProxyBase. Can be called from blueprints or C++ as a static function
UCLASS()
class UNREALOPENAI_API UCreateImageVariationRequestBase64JSON : public UOnlineBlueprintCallProxyBase
{
	GENERATED_BODY()

public:
	/**
	 * Fired when the create image variation base64 JSON request is successful, will
	 * return the response in FCreateImageResponseBase64JSON struct, a valid JSON string
	 * response and an empty error string  
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnSuccess;

	/**
	 * Fired when the create image variation base64 JSON request fails, will return an
	 * empty FCreateImageResponseBase64JSON struct, JSON string error response, and an
	 * error string
	 */
	UPROPERTY(BlueprintAssignable)
	FCreateImageVariationRequestCallbackSignatureBase64JSON OnFailure;

	/**
	 * Implementation of the create image variation base64 JSON request API call as
	 * defined in: https://beta.openai.com/docs/api-reference/images/create-variation
	 *
	 * Creates a variation of a given image.
	 * @param WorldContextObject Function caller to obtain world context
	 * @param ImageFile The image to edit. Can be obtained using
	 * UUnrealOpenAIUtils::OpenLoadImageDialog
	 * Must be a valid PNG file, less than 4MB, and square.
	 * @param ImageSize The size of the generated images. 
	 * @return The proxy object to use for the request
	 */
	UFUNCTION(BlueprintCallable, meta=(BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "UnrealOpenAI | Image")
	static UCreateImageVariationRequestBase64JSON* CreateImageVariationJSON(UObject* WorldContextObject, FFileToLoad ImageFile, EImageSize ImageSize);

	/**
	 * Activates the create image variation base64 JSON request proxy, call this function
	 * in C++ to execute the request  
	 */
	virtual void Activate() override;

private:
	/**
	 * Proxy's world context object
	 */
	UObject* WorldContextObject;

	/**
	 * Current request's image file
	 */
	FFileToLoad ImageFile;

	/**
	 * Current request's image size
	 */
	EImageSize ImageSize;
};


#pragma endregion 