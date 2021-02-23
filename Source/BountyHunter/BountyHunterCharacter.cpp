// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BountyHunterCharacter.h"
#include "BountyHunterProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"

#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "Components/SkeletalMeshComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"

#include "HeadMountedDisplayFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "MotionControllerComponent.h"
#include "XRMotionControllerBase.h" // for FXRMotionControllerBase::RightHandSourceId

#include <BountyHunter/Character/fsm/states/movement/Idle.h>
#include <BountyHunter/Character/fsm/states/movement/Walk.h>

#include <BountyHunter/Character/fsm/states/debug/Debug.h>
#include <BountyHunter/Character/fsm/states/debug/Normal.h>
#include <BountyHunter/Character/fsm/states/debug/NextNPC.h>
#include <BountyHunter/Character/fsm/states/debug/PreviousNPC.h>

#include <BountyHunter/Character/fsm/states/abilities/Casting.h>
#include <BountyHunter/Character/fsm/states/abilities/IdleAbility.h>
#include <BountyHunter/Character/fsm/states/abilities/Cooldown.h>

#include <BountyHunter/Character/fsm/transitions/movement/EnterIdle.h>
#include <BountyHunter/Character/fsm/transitions/movement/EnterWalk.h>

#include <BountyHunter/Character/fsm/transitions/abilities/EnterCast.h>
#include <BountyHunter/Character/fsm/transitions/abilities/EnterIdleAbility.h>
#include <BountyHunter/Character/fsm/transitions/abilities/EnterCooldown.h>

#include <BountyHunter/Character/fsm/transitions/debug/EnterNormal.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterDebug.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterNextNPC.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterPreviousNPC.h>
#include <BountyHunter/Character/fsm/transitions/debug/LeaveState.h>

#include <BountyHunter/Character/InputHandler.h>

#include <BountyHunter/Abilities/IAbility.h>
#include <BountyHunter/Abilities/Ability.h>
#include <BountyHunter/Abilities/HealthAbility.h>

#include <BountyHunter/Abilities/DataAssets/DA_CharacterAbility.h>

#include <BountyHunter/BountyHunterGameMode.h>

#include <memory>

#include <cassert>

#include "FSM/StatesMachineFactory.h"

using namespace TLN;
DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);

//////////////////////////////////////////////////////////////////////////
// ABountyHunterCharacter

ABountyHunterCharacter::ABountyHunterCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

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

	mInputHandler = std::make_shared<InputHandler>();
	mAttributes = std::make_shared<TLN::CharacterAttributes>();
	//TODO DebugData must be initialized with the first npc character
	//but, no sé si en este punto ya se han creado los npc. Habría que 
	//verlo y pensar donde va esto que necesita el character para la maquina de estados.
	mDebugData = std::make_unique<DebugData>();

	FillUpCharacterAttributes();
	FillUpAbilitiesFactory();
	CreateStatesMachine();
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

	//UE_LOG(LogTemp, Log, TEXT("[TheLastKnightCharacter][Tick] Character FSM:"));
	mStatesMachineController.Update(DeltaSeconds);
	//UE_LOG(LogTemp, Log, TEXT("[TheLastKnightCharacter][Tick] Character FSM state: %d"), machine->GetCurrentState()->GetID());
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
	return mStatesMachineController.GetCurrentStateID(1) == CharacterState::STATE_CASTING;
}

bool ABountyHunterCharacter::IsReadyToCast() const
{
	return mAbilitiesToolBelt.IsReadyToCast();
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

std::shared_ptr<TLN::IAbility> ABountyHunterCharacter::Cast()
{
	TLN::InputAction action = InputAction::ABILITY1;

	if (mInputHandler->IsActionPressed(InputAction::ABILITY1))
	{
		action = InputAction::ABILITY1;
	}
	else if (mInputHandler->IsActionPressed(InputAction::ABILITY2))
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

//////////////////////////////////////////////////////////////////////////
// Input

void ABountyHunterCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// set up gameplay key bindings
	check(PlayerInputComponent);

	// Bind jump events
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	// Bind fire event
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ABountyHunterCharacter::OnFire);

	// Enable touchscreen input
	EnableTouchscreenMovement(PlayerInputComponent);

	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ABountyHunterCharacter::OnResetVR);

	// Bind movement events
	PlayerInputComponent->BindAxis("MoveForward", this, &ABountyHunterCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ABountyHunterCharacter::MoveRight);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("Ability1", IE_Pressed, this, &ABountyHunterCharacter::PressKey, TLN::InputAction::ABILITY1);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("Ability1", IE_Released, this, &ABountyHunterCharacter::ReleaseKey, TLN::InputAction::ABILITY1);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("Ability2", IE_Pressed, this, &ABountyHunterCharacter::PressKey, TLN::InputAction::ABILITY2);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("Ability2", IE_Released, this, &ABountyHunterCharacter::ReleaseKey, TLN::InputAction::ABILITY2);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("EnableDebugMode", IE_Pressed, this, &ABountyHunterCharacter::PressKey, TLN::InputAction::ENTER_LEAVE_DEBUG);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("EnableDebugMode", IE_Released, this, &ABountyHunterCharacter::ReleaseKey, TLN::InputAction::ENTER_LEAVE_DEBUG);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("NextNPC", IE_Pressed, this, &ABountyHunterCharacter::PressKey, TLN::InputAction::NEXT_NPC);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("NextNPC", IE_Released, this, &ABountyHunterCharacter::ReleaseKey, TLN::InputAction::NEXT_NPC);

	PlayerInputComponent->BindAction<FPressKeyDelegate>("PreviousNPC", IE_Pressed, this, &ABountyHunterCharacter::PressKey, TLN::InputAction::PREVIOUS_NPC);
	PlayerInputComponent->BindAction<FReleaseKeyDelegate>("PreviousNPC", IE_Released, this, &ABountyHunterCharacter::ReleaseKey, TLN::InputAction::PREVIOUS_NPC);

	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ABountyHunterCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ABountyHunterCharacter::LookUpAtRate);
}

void ABountyHunterCharacter::CreateStatesMachine()
{
	mCharacterFSMContext = std::make_shared<CharacterContext>(
		GetWorld(),
		this,
		mInputHandler,
		mDebugData);
	
	StatesMachineFactory factory;
	
	mStatesMachineController.AddMachine(std::move(factory.Create<CharacterState, CharacterContext>(FSMType::CHARACTER_MOVEMENT, mCharacterFSMContext)));
	mStatesMachineController.AddMachine(std::move(factory.Create<CharacterState, CharacterContext>(FSMType::CHARACTER_ABILITY, mCharacterFSMContext)));
	mStatesMachineController.AddMachine(std::move(factory.Create<CharacterState, CharacterContext>(FSMType::DEBUG, mCharacterFSMContext)));
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
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
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

void ABountyHunterCharacter::OnResetVR()
{
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ABountyHunterCharacter::BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == true)
	{
		return;
	}
	if ((FingerIndex == TouchItem.FingerIndex) && (TouchItem.bMoved == false))
	{
		OnFire();
	}
	TouchItem.bIsPressed = true;
	TouchItem.FingerIndex = FingerIndex;
	TouchItem.Location = Location;
	TouchItem.bMoved = false;
}

void ABountyHunterCharacter::EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	if (TouchItem.bIsPressed == false)
	{
		return;
	}
	TouchItem.bIsPressed = false;
}

//Commenting this section out to be consistent with FPS BP template.
//This allows the user to turn without using the right virtual joystick

//void ABountyHunterCharacter::TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location)
//{
//	if ((TouchItem.bIsPressed == true) && (TouchItem.FingerIndex == FingerIndex))
//	{
//		if (TouchItem.bIsPressed)
//		{
//			if (GetWorld() != nullptr)
//			{
//				UGameViewportClient* ViewportClient = GetWorld()->GetGameViewport();
//				if (ViewportClient != nullptr)
//				{
//					FVector MoveDelta = Location - TouchItem.Location;
//					FVector2D ScreenSize;
//					ViewportClient->GetViewportSize(ScreenSize);
//					FVector2D ScaledDelta = FVector2D(MoveDelta.X, MoveDelta.Y) / ScreenSize;
//					if (FMath::Abs(ScaledDelta.X) >= 4.0 / ScreenSize.X)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.X * BaseTurnRate;
//						AddControllerYawInput(Value);
//					}
//					if (FMath::Abs(ScaledDelta.Y) >= 4.0 / ScreenSize.Y)
//					{
//						TouchItem.bMoved = true;
//						float Value = ScaledDelta.Y * BaseTurnRate;
//						AddControllerPitchInput(Value);
//					}
//					TouchItem.Location = Location;
//				}
//				TouchItem.Location = Location;
//			}
//		}
//	}
//}

void ABountyHunterCharacter::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !IsCasting())
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		AddMovementInput(Direction, Value);
	}
}

void ABountyHunterCharacter::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f) && !IsCasting())
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void ABountyHunterCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABountyHunterCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABountyHunterCharacter::PressKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, true);
}

void ABountyHunterCharacter::ReleaseKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, false);
}

bool ABountyHunterCharacter::EnableTouchscreenMovement(class UInputComponent* PlayerInputComponent)
{
	if (FPlatformMisc::SupportsTouchInput() || GetDefault<UInputSettings>()->bUseMouseForTouch)
	{
		PlayerInputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABountyHunterCharacter::BeginTouch);
		PlayerInputComponent->BindTouch(EInputEvent::IE_Released, this, &ABountyHunterCharacter::EndTouch);

		//Commenting this out to be more consistent with FPS BP template.
		//PlayerInputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABountyHunterCharacter::TouchUpdate);
		return true;
	}
	
	return false;
}
