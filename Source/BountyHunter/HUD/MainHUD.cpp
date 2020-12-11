// Fill out your copyright notice in the Description page of Project Settings.


#include <BountyHunter/HUD/MainHUD.h>

#include <BountyHunter/utils/UtilsLibrary.h>
#include <BountyHunter/BountyHunterGameMode.h>

#include <BountyHunter/Debug/HUD/DebugHUDController.h>
#include <BountyHunter/Character/HUD/CharacterHUD.h>

#include <Kismet/GameplayStatics.h>

AMainHUD::AMainHUD() : mHudIndex{0}
{
	
}

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();
	
	CreateDebugHUD(DebugHUDWidgetClasses);
	CreateCharacterHUD(CharacterHUDWidgetClasses);
	
	BindToDelegate();
}

void AMainHUD::CreateDebugHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mDebugHUDController = GetWorld()->SpawnActor<ADebugHUDController>(
		ADebugHUDController::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);
	mDebugHUDController->Initialize(mHudIndex, GetOwningPlayerController(), widgetClasses);
}

void AMainHUD::CreateCharacterHUD(TArray<TSubclassOf<UUserWidget>> widgetClasses)
{
	FActorSpawnParameters spawnInfo;
	spawnInfo.Owner = this;
	//spawnInfo.Instigator = this;
	spawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mCharacterHUD = GetWorld()->SpawnActor<ACharacterHUD>(
		ACharacterHUD::StaticClass(),
		FVector::ZeroVector,
		FRotator::ZeroRotator,
		spawnInfo);
	mCharacterHUD->Initialize(mHudIndex, GetOwningPlayerController(), widgetClasses);
}

void AMainHUD::BindToDelegate()
{
	auto gameMode = Cast<ABountyHunterGameMode>(UGameplayStatics::GetGameMode(GetOwningPawn()->GetWorld()));
	if (gameMode)
	{
		
	}
}