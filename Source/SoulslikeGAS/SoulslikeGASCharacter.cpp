// Copyright Epic Games, Inc. All Rights Reserved.

#include "SoulslikeGASCharacter.h"
#include "Engine/LocalPlayer.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "AbilitySystemComponent.h"
#include "Public/AttributeSet/SoulsAttributeSet.h"
#include "RPGPlayerState.h"
#include "AbilitySystem/RPGAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DataAsset/CharacterClassInfoDataAsset.h"
#include "Library/RPGAbilitySystemLibrary.h"

//////////////////////////////////////////////////////////////////////////
// ASoulslikeGASCharacter

ASoulslikeGASCharacter::ASoulslikeGASCharacter()
{
	AbilitySystemComp = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComp"));
	AbilitySystemComp->SetIsReplicated(true);
	AbilitySystemComp->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);

	Attributes = CreateDefaultSubobject<USoulsAttributeSet>(TEXT("Attributes"));
}

void ASoulslikeGASCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (HasAuthority())
	{
		InitAbilityActorInfo();
	}
}

void ASoulslikeGASCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

void ASoulslikeGASCharacter::InitAbilityActorInfo()
{
	if (ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>())
	{
		RPGAbilitySystemComp = RPGPlayerState->GetRPGAbilitySystemComponent();
		RPGAttributes = RPGPlayerState->GetRPGAttributes();

		if (IsValid(RPGAbilitySystemComp))
		{
			RPGAbilitySystemComp->InitAbilityActorInfo(RPGPlayerState, this);

			if (HasAuthority())
			{
				InitClassDefaults();
			}
		}
	}
}

void ASoulslikeGASCharacter::InitClassDefaults()
{
	if (!CharacterTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("No Character Tag Selected In This Character %s"), *GetNameSafe(this));
	}
	else if (UCharacterClassInfoDataAsset* ClassInfo = URPGAbilitySystemLibrary::GetCharacterClassDefaultInfo(this))
	{
		if (const FCharacterClassDefaultInfo* SelectedClassInfo = ClassInfo->ClassDefaultInfoMap.Find(CharacterTag))
		{
			if (IsValid(RPGAbilitySystemComp))
			{
				RPGAbilitySystemComp->AddCharacterAbilities(SelectedClassInfo->StartingAbilities);
				RPGAbilitySystemComp->AddCharacterPassiveAbilities(SelectedClassInfo->StartingPassives);
				RPGAbilitySystemComp->InitializeDefaultAttributes(SelectedClassInfo->DefaultAttributes);
			}
		}
	}
}

void ASoulslikeGASCharacter::BeginPlay()
{
	Super::BeginPlay();


}

//////////////////////////////////////////////////////////////////////////
// Input

void ASoulslikeGASCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASoulslikeGASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ASoulslikeGASCharacter::StartJump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ASoulslikeGASCharacter::StopJump);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASoulslikeGASCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASoulslikeGASCharacter::Look);

		// Attack
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Triggered, this, &ASoulslikeGASCharacter::Attack);

		// Block
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ASoulslikeGASCharacter::Block);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Ongoing, this, &ASoulslikeGASCharacter::Block);
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Completed, this, &ASoulslikeGASCharacter::Block);

		// Roll
		EnhancedInputComponent->BindAction(BlockAction, ETriggerEvent::Triggered, this, &ASoulslikeGASCharacter::Roll);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

bool ASoulslikeGASCharacter::IsAir()
{
	UCharacterMovementComponent* MovementComp = GetCharacterMovement();

	bool isInAir = (MovementComp->MovementMode == EMovementMode::MOVE_Falling);
	return isInAir;
}

void ASoulslikeGASCharacter::StartJump(const FInputActionValue& Value)
{
	
}

void ASoulslikeGASCharacter::StopJump(const FInputActionValue& Value)
{

}

void ASoulslikeGASCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASoulslikeGASCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASoulslikeGASCharacter::Attack(const FInputActionValue& Value)
{
	if (!IsAir())
	{
		
	}
}

void ASoulslikeGASCharacter::Block(const FInputActionValue& Value)
{
	if (!IsAir())
	{

	}
}

void ASoulslikeGASCharacter::Roll(const FInputActionValue& Value)
{
	if (!IsAir())
	{

	}
}
