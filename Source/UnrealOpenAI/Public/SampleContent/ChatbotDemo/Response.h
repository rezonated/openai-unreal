// Created, maintained by Vanan A. - rezonated @ github.com

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Response.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UResponse : public UInterface
{
	GENERATED_BODY()
};

// Simple interface to set the response from AI or User
class UNREALOPENAI_API IResponse
{
	GENERATED_BODY()

public:
	/**
	 * Should implement this to set the response 
	 * @param Response Response to display
	 */
	virtual void SetResponse(FString Response);
};
