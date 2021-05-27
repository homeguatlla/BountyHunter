// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BountyHunterCharacter.h"
#include "BountyHunterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "BountyHunterGameInstance.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"
#include "GameFramework/Pawn.h"

#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

#include <BountyHunter/BountyHunterGameMode.h>
#include <BountyHunter/BountyHunterPlayerController.h>
#include <BountyHunter/Character/InputHandler.h>
#include <BountyHunter/Character/IBHPlayerController.h>
#include <BountyHunter/Abilities/IAbility.h>
#include <BountyHunter/Abilities/Ability.h>
#include <BountyHunter/Abilities/HealthAbility.h>
#include <BountyHunter/Abilities/DataAssets/DA_CharacterAbility.h>


#include <memory>
#include <cassert>

#include "BountyHunterGameInstance.h"


using namespace TLN;
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ABountyHunterCharacter

ABountyHunterCharacter::ABountyHunterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	Mesh1P->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));

	// Create a gun mesh component
	FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
	FP_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	FP_Gun->bCastDynamicShadow = false;
	FP_Gun->CastShadow = false;
	// FP_Gun->SetupAttachment(Mesh1P, TEXT("GripPoint"));
	FP_Gun->SetupAttachment(RootComponent);

	FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
	FP_MuzzleLocation->SetupAttachment(FP_Gun);
	FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 48.4f, -10.6f));

	// Default offset from the character location for projectiles to spawn
	GunOffset = FVector(100.0f, 0.0f, 10.0f);

	// Note: The ProjectileClass and the skeletal mesh/anim blueprints for Mesh1P, FP_Gun, and VR_Gun 
	// are set in the derived blueprint asset named MyCharacter to avoid direct content references in C++.

	// Create VR Controllers.
	R_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("R_MotionController"));
	R_MotionController->MotionSource = FXRMotionControllerBase::RightHandSourceId;
	R_MotionController->SetupAttachment(RootComponent);
	L_MotionController = CreateDefaultSubobject<UMotionControllerComponent>(TEXT("L_MotionController"));
	L_MotionController->SetupAttachment(RootComponent);

	// Create a gun and attach it to the right-hand VR controller.
	// Create a gun mesh component
	VR_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VR_Gun"));
	VR_Gun->SetOnlyOwnerSee(true);			// only the owning player will see this mesh
	VR_Gun->bCastDynamicShadow = false;
	VR_Gun->CastShadow = false;
	VR_Gun->SetupAttachment(R_MotionController);
	VR_Gun->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));

	VR_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("VR_MuzzleLocation"));
	VR_MuzzleLocation->SetupAttachment(VR_Gun);
	VR_MuzzleLocation->SetRelativeLocation(FVector(0.000004, 53.999992, 10.000000));
	VR_MuzzleLocation->SetRelativeRotation(FRotator(0.0f, 90.0f, 0.0f));		// Counteract the rotation of the VR gun model.

	// Uncomment the following line to turn motion controllers on by default:
	//bUsingMotionControllers = true;
}

void ABountyHunterCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
	FP_Gun->AttachToComponent(Mesh1P, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("GripPoint"));

	// Show or hide the two versions of the gun based on whether or not we're using motion controllers.
	if (bUsingMotionControllers)
	{
		VR_Gun->SetHiddenInGame(false, true);
		Mesh1P->SetHiddenInGame(true, true);
	}
	else
	{
		VR_Gun->SetHiddenInGame(true, true);
		Mesh1P->SetHiddenInGame(false, true);
	}

	mAttributes = std::make_shared<TLN::CharacterAttributes>();
	
	FillUpCharacterAttributes();
	FillUpAbilitiesFactory();
	AddDefaultAbilitiesToTheAbilitiesToolChest();
}

void ABountyHunterCharacter::NotifyStartAttributeValues() const
{
	auto gameMode = GetWorld()->GetAuthGameMode<ABountyHunterGameMode>();
	if (gameMode)
	{
		gameMode->GetEventDispatcher()->OnUpdateHealth.Broadcast(mAttributes->GetHealth());
	}
}

void ABountyHunterCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!mHasNotifiedData)
	{
		NotifyStartAttributeValues();
		mAbilitiesToolBelt.Initialize();
		mHasNotifiedData = true;
	}
}

bool ABountyHunterCharacter::IsWalking() const
{
	const auto characterMovement = GetCharacterMovement();
	return characterMovement->IsWalking() && !characterMovement->Velocity.IsZero();
}

bool ABountyHunterCharacter::IsIdle() const
{
	const auto characterMovement = GetCharacterMovement();
	return characterMovement->IsWalking() && characterMovement->Velocity.IsZero();
}

bool ABountyHunterCharacter::IsCasting() const
{
	return GetPlayerController()->GetCurrentStateID(1) == CharacterState::STATE_CASTING;
}

const IBHPlayerController* ABountyHunterCharacter::GetPlayerController() const
{
	return GetController<ABountyHunterPlayerController>();
}

bool ABountyHunterCharacter::IsReadyToCast() const
{
	return mAbilitiesToolBelt.IsReadyToCast();
}

bool ABountyHunterCharacter::IsReadyToFire() const
{
	return true;
}

void ABountyHunterCharacter::PlayCastingAnimation()
{
	IsCastingOneHeight = true;
}

void ABountyHunterCharacter::StopCastingAnimation()
{
	IsCastingOneHeight = false;
}

bool ABountyHunterCharacter::CanCast(InputAction action) const
{
	return mAbilitiesToolBelt.CanCast(action, mAttributes->GetMana());
}

//TODO hay que revisar esto.
//en la transición para entrar en cast se comprueba el CanCast y se pasa la acción.
//es el mismo código que tenemos aquí. De alguna manera, tendríamos que tener un método
//que nos diga si alguna habilidad ha sido activada y nos la devuelva.
//y entonces hacemos un Cast(action).
//el ToolBelt tiene que tener algo parecido a HasActionAbilityBinded(action) -->true/false
//de esta manera ya podemos quitar estos ifs de todas partes. Esto último no parece servir para resolver.
//El EnterCast y el Cast repiten código. 
//Cuando haces Cast quizá debería ser Cast(action) y diria que el toolbelt es el que te proporciona el action basado en un input
//hay que darle vueltas pero se tiene que arreglar pues ahora mismo otra habilidad requiere muchas modificaciones.
//cuando con solo añadir la abilidad al toolbelt ya se podría hacer todo.

std::shared_ptr<IAbility> ABountyHunterCharacter::Cast()
{
	InputAction action = InputAction::ABILITY1;

	const auto controller = GetPlayerController();
	if (controller->IsActionPressed(InputAction::ABILITY1))
	{
		action = InputAction::ABILITY1;
	}
	else if (controller->IsActionPressed(InputAction::ABILITY2))
	{
		action = InputAction::ABILITY2;
	}

	auto ability = mAbilitiesToolBelt.GetAbility(action);
	if (ability)
	{
		mAttributes->SetMana(mAttributes->GetMana() - ability->GetCastCost());
		ability->CastSpell(GetActorLocation());
	}

	return ability;
}

bool ABountyHunterCharacter::CanFire() const
{
	return true;
}

void ABountyHunterCharacter::Fire()
{
	OnFire();
}

void ABountyHunterCharacter::FillUpCharacterAttributes()
{
	if (CharacterAttributes)
	{
		const uint8 maxHealth = CharacterAttributes->GetMaxHealth();
		assert(maxHealth > 0);
		mAttributes->SetMaxHealth(maxHealth);

		const uint8 maxMana = CharacterAttributes->GetMaxMana();
		assert(maxMana > 0);
		mAttributes->SetMaxMana(maxMana);
	}
}

void ABountyHunterCharacter::FillUpAbilitiesFactory()
{
	mAbilitiesFactory = std::make_shared<AbilitiesFactory>(mCharacterAbilities);
	mAbilitiesFactory->Register(
		HealthAbility::GetName(),
		[this](AAbility* ability, UDA_CharacterAbility* abilityDA)
		{
			return HealthAbility::Create(ability, abilityDA, mAttributes);
		}
	);
} 

void ABountyHunterCharacter::AddDefaultAbilitiesToTheAbilitiesToolChest()
{
	auto ability = mAbilitiesFactory->Create(HealthAbility::GetName(), GetWorld(), this);
	auto index = mAbilitiesToolBelt.AddAbility(ability);
	mAbilitiesToolBelt.BindAbilityToToolBelt(TLN::InputAction::ABILITY1, index);
	mAbilitiesToolBelt.BindAbilityToToolBelt(TLN::InputAction::ABILITY2, index);
}

void ABountyHunterCharacter::PerformMovement()
{

}

void ABountyHunterCharacter::OnFire()
{
	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			if (bUsingMotionControllers)
			{
				const FRotator SpawnRotation = VR_MuzzleLocation->GetComponentRotation();
				const FVector SpawnLocation = VR_MuzzleLocation->GetComponentLocation();
				World->SpawnActor<ABountyHunterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
			}
			else
			{
				const FRotator SpawnRotation = GetControlRotation();
				// MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
				const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

				//Set Spawn Collision Handling Override
				FActorSpawnParameters ActorSpawnParams;
				ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

				// spawn the projectile at the muzzle
				World->SpawnActor<ABountyHunterProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
			}
		}
	}

	// try and play the sound if specified
	if (FireSound != NULL)
	{
		const auto gameInstance = GetGameInstance<UBountyHunterGameInstance>();
		check(gameInstance);
		gameInstance->GetSoundPlayer()->PlaySound(this, FireSound, GetActorLocation());
	}

	// try and play a firing animation if specified
	if (FireAnimation != NULL)
	{
		// Get the animation object for the arms mesh
		UAnimInstance* AnimInstance = Mesh1P->GetAnimInstance();
		if (AnimInstance != NULL)
		{
			AnimInstance->Montage_Play(FireAnimation, 1.f);
		}
	}
}
