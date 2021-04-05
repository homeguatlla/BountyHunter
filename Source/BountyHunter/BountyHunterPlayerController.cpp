// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyHunterPlayerController.h"


#include "BountyHunterCharacter.h"
#include "Debug/DebugData.h"
#include "FSM/StatesMachineFactory.h"
#include "GameFramework/InputSettings.h"

void ABountyHunterPlayerController::BeginPlay()
{
	Super::BeginPlay();

	// set our turn rates for input
	mBaseTurnRate = 45.f;
	mBaseLookUpRate = 45.f;
	
	//TODO DebugData must be initialized with the first npc character
	//but, no sé si en este punto ya se han creado los npc. Habría que 
	//verlo y pensar donde va esto que necesita el character para la maquina de estados.
	mDebugData = std::make_unique<DebugData>();
	mInputHandler = std::make_shared<TLN::InputHandler>();
	CreateStatesMachine();
}

void ABountyHunterPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// set up gameplay key bindings
	check(InputComponent);

	// Bind jump events
	/*InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
*/
	// Bind movement events
	InputComponent->BindAxis("MoveForward", this, &ABountyHunterPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABountyHunterPlayerController::MoveRight);

	// Bind fire event
	InputComponent->BindAction<FPressKeyDelegate>("Jump", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::JUMP);
	InputComponent->BindAction<FReleaseKeyDelegate>("Jump", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::JUMP);

	InputComponent->BindAction<FPressKeyDelegate>("Fire", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::FIRE);
	InputComponent->BindAction<FReleaseKeyDelegate>("Fire", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::FIRE);

	InputComponent->BindAction<FPressKeyDelegate>("Ability1", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::ABILITY1);
	InputComponent->BindAction<FReleaseKeyDelegate>("Ability1", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::ABILITY1);

	InputComponent->BindAction<FPressKeyDelegate>("Ability2", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::ABILITY2);
	InputComponent->BindAction<FReleaseKeyDelegate>("Ability2", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::ABILITY2);

	InputComponent->BindAction<FPressKeyDelegate>("EnableDebugMode", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::ENTER_LEAVE_DEBUG);
	InputComponent->BindAction<FReleaseKeyDelegate>("EnableDebugMode", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::ENTER_LEAVE_DEBUG);

	InputComponent->BindAction<FPressKeyDelegate>("NextNPC", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::NEXT_NPC);
	InputComponent->BindAction<FReleaseKeyDelegate>("NextNPC", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::NEXT_NPC);

	InputComponent->BindAction<FPressKeyDelegate>("PreviousNPC", IE_Pressed, this, &ABountyHunterPlayerController::PressKey, TLN::InputAction::PREVIOUS_NPC);
	InputComponent->BindAction<FReleaseKeyDelegate>("PreviousNPC", IE_Released, this, &ABountyHunterPlayerController::ReleaseKey, TLN::InputAction::PREVIOUS_NPC);

	
	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	InputComponent->BindAxis("Turn", this, &ABountyHunterPlayerController::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &ABountyHunterPlayerController::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &ABountyHunterPlayerController::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &ABountyHunterPlayerController::LookUpAtRate);
}

void ABountyHunterPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	//UE_LOG(LogTemp, Log, TEXT("[TheLastKnightCharacter][Tick] Character FSM:"));
	mStatesMachineController.Update(DeltaSeconds);
	//UE_LOG(LogTemp, Log, TEXT("[TheLastKnightCharacter][Tick] Character FSM state: %d"), machine->GetCurrentState()->GetID());
}

void ABountyHunterPlayerController::CreateStatesMachine()
{
	const auto character = Cast<ABountyHunterCharacter>(GetCharacter());
	mCharacterFSMContext = std::make_shared<TLN::CharacterContext>(
        GetWorld(),
        character,
        mInputHandler,
        mDebugData);

	TLN::StatesMachineFactory factory;
	
	mStatesMachineController.AddMachine(std::move(factory.CreateCharacter(FSMType::CHARACTER_MOVEMENT, mCharacterFSMContext)));
	mStatesMachineController.AddMachine(std::move(factory.CreateCharacter(FSMType::CHARACTER_ABILITY, mCharacterFSMContext)));
	mStatesMachineController.AddMachine(std::move(factory.CreateCharacter(FSMType::DEBUG, mCharacterFSMContext)));
}

void ABountyHunterPlayerController::PressKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, true);
}

void ABountyHunterPlayerController::ReleaseKey(TLN::InputAction action)
{
	mInputHandler->InsertInput(action, false);
}

void ABountyHunterPlayerController::MoveForward(float Value)
{
	const TLN::ICharacter* character = Cast<ABountyHunterCharacter>(GetCharacter());
	if (Value != 0.0f && !character->IsCasting())
	{
		// find out which way is fcharacterrward
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		GetCharacter()->AddMovementInput(Direction, Value);
	}
}

void ABountyHunterPlayerController::MoveRight(float Value)
{
	const TLN::ICharacter* character = Cast<ABountyHunterCharacter>(GetCharacter());
	if (Value != 0.0f && !character->IsCasting())
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		GetCharacter()->AddMovementInput(Direction, Value);
	}
}

void ABountyHunterPlayerController::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetCharacter()->AddControllerYawInput(Rate * mBaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ABountyHunterPlayerController::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	GetCharacter()->AddControllerPitchInput(Rate * mBaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ABountyHunterPlayerController::AddControllerYawInput(float Val)
{
	GetCharacter()->AddControllerYawInput(Val);
}

void ABountyHunterPlayerController::AddControllerPitchInput(float Val)
{
	GetCharacter()->AddControllerPitchInput(Val);
}