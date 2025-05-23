// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "CharacterClassInfoDataAsset.generated.h"

class UGameplayEffect;
class UGameplayAbility;

USTRUCT()
struct FCharacterClassDefaultInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DefaultAttributes;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingAbilities;

	UPROPERTY(EditDefaultsOnly)
	TArray<TSubclassOf<UGameplayAbility>> StartingPassives;
};

/**
 * 
 */
UCLASS()
class SOULSLIKEGAS_API UCharacterClassInfoDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, FCharacterClassDefaultInfo> ClassDefaultInfoMap;
};
