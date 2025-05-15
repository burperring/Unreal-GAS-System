// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGAbilitySystemLibrary.generated.h"

class UCharacterClassInfoDataAsset;

/**
 * 
 */
UCLASS()
class SOULSLIKEGAS_API URPGAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintPure)
	static UCharacterClassInfoDataAsset* GetCharacterClassDefaultInfo(const UObject* WorldContextObject);
};
