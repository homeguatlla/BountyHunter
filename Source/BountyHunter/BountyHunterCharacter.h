// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include <NAI/include/utils/fsm/StatesMachine.h>
#include <BountyHunter/Character/CharacterAttributes.h>
#include <BountyHunter/Character/DA_CharacterAttributes.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/InputHandler.h>
#include <BountyHunter/Character/AbilitiesToolBelt.h>
#include <BountyHunter/Abilities/AbilitiesFactory.h>

#include "BountyHunterCharacter.generated.h"

namespace TLN
{
	class IBHPlayerController;
}
class UInputComponent;
class UDA_CharacterAbilities;

DECLARE_DELEGATE_OneParam(FPressKeyDelegate, TLN::InputAction);
DECLARE_DELEGATE_OneParam(FReleaseKeyDelegate, TLN::InputAction);


UCLASS(config=Game)
class ABountyHunterCharacter : public ACharacter, public TLN::ICharacter
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

	std::shared_ptr<TLN::AbilitiesFactory> mAbilitiesFactory;

	bool mHasNotifiedData;
	
public:
	ABountyHunterCharacter();

protected:
	virtual void BeginPlay();

public:
	

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
	const TLN::IBHPlayerController* GetPlayerController() const;
		
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

private:
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

