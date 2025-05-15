// Fill out your copyright notice in the Description page of Project Settings.


#include "Library/RPGAbilitySystemLibrary.h"
#include "Game/RPGGameMode.h"
#include "Kismet/GameplayStatics.h"

UCharacterClassInfoDataAsset* URPGAbilitySystemLibrary::GetCharacterClassDefaultInfo(const UObject* WorldContextObject)
{
	if (const ARPGGameMode* RPGGameMode = Cast<ARPGGameMode>(UGameplayStatics::GetGameMode(WorldContextObject)))
	{
		return RPGGameMode->GetCharacterClassDefaultInfo();
	}

	return nullptr;
}
