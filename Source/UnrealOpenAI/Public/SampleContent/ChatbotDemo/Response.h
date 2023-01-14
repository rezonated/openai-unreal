// Fill out your copyright notice in the Description page of Project Settings.

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

/**
 * 
 */
class UNREALOPENAI_API IResponse
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void SetResponse(FString Response);
};
