// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include <NAI/include/utils/fsm/StatesMachine.h>

#include <BountyHunter/Character/CharacterAttributes.h>
#include <BountyHunter/Character/DA_CharacterAttributes.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/InputHandler.h>
#include <BountyHunter/Character/AbilitiesToolBelt.h>
#include <BountyHunter/Abilities/AbilitiesFactory.h>
#include <BountyHunter/Debug/DebugData.h>
#include "BountyHunterCharacter.generated.h"

class UInputComponent;
using TLN::ICharacter;
class UDA_CharacterAbilities;

DECLARE_DELEGATE_OneParam(FPressKeyDelegate, TLN::InputAction);
DECLARE_DELEGATE_OneParam(FReleaseKeyDelegate, TLN::InputAction);


UCLASS(config=Game)
class ABountyHunterCharacter : public ACharacter, public ICharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	class USkeletalMeshComponent* Mesh1P;

	/** Gun mesh: 1st person view (seen only by self) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* FP_Gun;

	/** Location on gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* FP_MuzzleLocation;

	/** Gun mesh: VR view (attached to the VR controller directly, no arm, just the actual gun) */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* VR_Gun;

	/** Location on VR gun mesh where projectiles should spawn. */
	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USceneComponent* VR_MuzzleLocation;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCameraComponent;

	/** Motion controller (right hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UMotionControllerComponent* R_MotionController;

	/** Motion controller (left hand) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	
	class UMotionControllerComponent* L_MotionController;
	//Custom attributes
	std::shared_ptr<TLN::CharacterAttributes> mAttributes;

	//Abilities Tool Chest
	//TLN::AbilitiesToolChest mAbilitiesToolChest;
	//Abilities Tool belt
	TLN::AbilitiesToolBelt mAbilitiesToolBelt;

	//States machine to control character states
	using StatesMachine = core::utils::FSM::StatesMachine<TLN::CharacterState, TLN::CharacterContext>;
	std::vector<std::unique_ptr<StatesMachine>> mStatesMachines;
	std::shared_ptr<TLN::CharacterContext> mCharacterFSMContext;

	//Holds last input
	std::shared_ptr<TLN::InputHandler> mInputHandler;

	std::shared_ptr<TLN::AbilitiesFactory> mAbilitiesFactory;

	std::shared_ptr<DebugData> mDebugData;

	bool mHasNotifiedData;
	
public:
	ABountyHunterCharacter();

protected:
	virtual void BeginPlay();

public:
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector GunOffset;

	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class ABountyHunterProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	class USoundBase* FireSound;

	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class UAnimMontage* FireAnimation;

	/** Whether to use motion controller location for aiming. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	uint32 bUsingMotionControllers : 1;

	/** Set to true when casting one hand height */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Animation)
	bool IsCastingOneHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Attributes")
	UDA_CharacterAttributes* CharacterAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Abilities")
	UDA_CharacterAbilities* mCharacterAbilities;
	
protected:
	
	/** Fires a projectile. */
	void OnFire();

	/** Resets HMD orientation and position in VR. */
	void OnResetVR();

	/** Handles moving forward/backward */
	void MoveForward(float Val);

	/** Handles stafing movement, left and right */
	void MoveRight(float Val);

	/**
	 * Called via input to turn at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate.
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	void Tick(float DeltaSeconds) override;

	//inherited from ICharacter
	bool IsWalking() const override;
	bool IsIdle() const override;
	bool IsCasting() const override;
	bool IsReadyToCast() const override;

	void PlayCastingAnimation() override;
	void StopCastingAnimation() override;

	bool CanCast(TLN::InputAction action) const override;
	std::shared_ptr<TLN::IAbility> Cast() override;
	
	void PressKey(TLN::InputAction action);
	void ReleaseKey(TLN::InputAction action);
	
	struct TouchData
	{
		TouchData() { bIsPressed = false;Location=FVector::ZeroVector;}
		bool bIsPressed;
		ETouchIndex::Type FingerIndex;
		FVector Location;
		bool bMoved;
	};
	void BeginTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void EndTouch(const ETouchIndex::Type FingerIndex, const FVector Location);
	void TouchUpdate(const ETouchIndex::Type FingerIndex, const FVector Location);
	TouchData	TouchItem;
	
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End of APawn interface

	/* 
	 * Configures input for touchscreen devices if there is a valid touch interface for doing so 
	 *
	 * @param	InputComponent	The input component pointer to bind controls to
	 * @returns true if touch controls were enabled.
	 */
	bool EnableTouchscreenMovement(UInputComponent* InputComponent);

private:
	void CreateStatesMachine();
	void CreateMovementStatesMachine();
	void CreateAbilityStatesMachine();
	void CreateDebugStatesMachine();
	void FillUpCharacterAttributes();
	void FillUpAbilitiesFactory();
	void AddDefaultAbilitiesToTheAbilitiesToolChest();
	void NotifyStartAttributeValues() const;

	//inherit from TLN::ICharacter
	void PerformMovement() override;
	
public:
	/** Returns Mesh1P subobject **/
	FORCEINLINE class USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

};

