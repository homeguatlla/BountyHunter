// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/IBHPlayerController.h"
#include "Character/fsm/CharacterContext.h"
#include "Character/fsm/states/CharacterStates.h"
#include "FSM/StatesMachineController.h"
#include "GameFramework/PlayerController.h"
#include "BountyHunterPlayerController.generated.h"

class DebugData;

UCLASS()
class ABountyHunterPlayerController : public APlayerController, public TLN::IBHPlayerController
{
	GENERATED_BODY()
	
public:
	TLN::CharacterState GetCurrentStateID(int machineId) const override{ return mStatesMachineController.GetCurrentStateID(machineId); }
	bool IsActionPressed(TLN::InputAction action) const override { return mInputHandler->IsActionPressed(action); }

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float mBaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float mBaseLookUpRate;

protected:
	void BeginPlay() override;
	void SetupInputComponent() override;
	void Tick(float DeltaSeconds) override;

		
private:
	void CreateStatesMachine();
	void PressKey(TLN::InputAction action);
	void ReleaseKey(TLN::InputAction action);

	void MoveForward(float Value);
	void MoveRight(float Value);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	void AddControllerYawInput(float Val);
	void AddControllerPitchInput(float Val);
	
	//States machine to control character states
	StatesMachineController<TLN::CharacterState, TLN::CharacterContext> mStatesMachineController;
	std::shared_ptr<TLN::CharacterContext> mCharacterFSMContext;

	//Holds last input
	std::shared_ptr<TLN::InputHandler> mInputHandler;
	std::shared_ptr<DebugData> mDebugData;	
};
