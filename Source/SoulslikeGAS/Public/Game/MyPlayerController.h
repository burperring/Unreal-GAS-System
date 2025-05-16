// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInventoryComponent;

/**
 * 
 */
UCLASS()
class SOULSLIKEGAS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	
	AMyPlayerController();
	
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProbs) const override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true), Replicated)
	TObjectPtr<UInventoryComponent> InventoryComp;
};
