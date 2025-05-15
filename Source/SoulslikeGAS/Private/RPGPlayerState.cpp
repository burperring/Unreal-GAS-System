// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerState.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "AttributeSet/SoulsAttributeSet.h"

ARPGPlayerState::ARPGPlayerState()
{
	NetUpdateFrequency = 100.0f;
	MinNetUpdateFrequency = 66.0f;

	RPGAbilitySystemComp = CreateDefaultSubobject<URPGAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	RPGAbilitySystemComp->SetIsReplicated(true);
	RPGAbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);

	RPGAttributes = CreateDefaultSubobject<USoulsAttributeSet>(TEXT("AttributesSet"));
}

UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
{
	return RPGAbilitySystemComp;
}

URPGAbilitySystemComponent* ARPGPlayerState::GetRPGAbilitySystemComponent() const
{
	return RPGAbilitySystemComp;
}

USoulsAttributeSet* ARPGPlayerState::GetRPGAttributes() const
{
	return RPGAttributes;
}
