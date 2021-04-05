// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "BountyHunterGameMode.h"
//#include "BountyHunterHUD.h"
#include "GameFramework/HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"

ABountyHunterGameMode::ABountyHunterGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// set default HUD class to our Blueprinted
	static ConstructorHelpers::FClassFinder<AHUD> MainHUDBPClass(TEXT("/Game/Game/Blueprints/HUD/BP_MainHUD"));
	if (MainHUDBPClass.Class != NULL)
	{
		HUDClass = MainHUDBPClass.Class;
	}

	// set default player controller class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/Game/Blueprints/Character/BP_PlayerController"));
	if(PlayerControllerClassFinder.Class != nullptr)
	{
		PlayerControllerClass = PlayerControllerClassFinder.Class;
	}
}

void ABountyHunterGameMode::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;


	mEventDispatcher = GetWorld()->SpawnActor<AEventDispatcher>(
		AEventDispatcher::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);

	mEventDispatcher->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, true));
}