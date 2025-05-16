// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/MyPlayerController.h"
#include "Inventory/InventoryComponent.h"
#include "Net/UnrealNetwork.h"

AMyPlayerController::AMyPlayerController()
{
	bReplicates = true;
	
	InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
	InventoryComp->SetIsReplicated(true);
}

void AMyPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyPlayerController, InventoryComp);
}
