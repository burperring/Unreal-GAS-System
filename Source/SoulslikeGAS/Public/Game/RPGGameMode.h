// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "RPGGameMode.generated.h"

class UCharacterClassInfoDataAsset;

/**
 * 
 */
UCLASS()
class SOULSLIKEGAS_API ARPGGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:

	UCharacterClassInfoDataAsset* GetCharacterClassDefaultInfo() const;

private:

	UPROPERTY(EditDefaultsOnly, Category = "CustomValue|ClassDefaults")
	TObjectPtr<UCharacterClassInfoDataAsset> ClassDefaults;
};
