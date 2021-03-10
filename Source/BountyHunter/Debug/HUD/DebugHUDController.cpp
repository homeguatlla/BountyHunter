// Fill out your copyright notice in the Description page of Project Settings.
#include <BountyHunter/Debug/HUD/DebugHUDController.h>
#include <BountyHunter/BountyHunterGameMode.h>
#include <BountyHunter/Debug/HUD/IDebugHUD.h>
#include <BountyHunter/Debug/HUD/IAgentDebugHUD.h>
#include <Kismet/GameplayStatics.h>
#include <BountyHunter/utils/UtilsLibrary.h>

const FString DEBUG_HUD_NAME("DebugHUDController");

ADebugHUDController::ADebugHUDController()
{

}

void ADebugHUDController::Initialize(
	int hudIndex, 
	APlayerController* playerController, 
	TArray<TSubclassOf<UUserWidget>> widgetsClasses)
{
	mDebugHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		DEBUG_HUD_NAME,
		playerController,
		widgetsClasses[0]);
	mAgentDebugHUDWidget = utils::UtilsLibrary::CreateHUDFromClass<UUserWidget>(
		hudIndex++, 
		DEBUG_HUD_NAME,
		playerController,
		widgetsClasses[1]);

	BindToDelegate();
}

void ADebugHUDController::BindToDelegate()
{
	auto gameMode = Cast<ABountyHunterGameMode>(UGameplayStatics::GetGameMode(this->GetWorld()));
	if (gameMode)
	{
		auto eventDispatcher = gameMode->GetEventDispatcher();

		eventDispatcher->OnEnableDebugMode.AddDynamic(this, &ADebugHUDController::OnEnableDebugMode);
		eventDispatcher->OnLogPredicate.AddDynamic(this, &ADebugHUDController::OnLogPredicate);
		eventDispatcher->OnLogClear.AddDynamic(this, &ADebugHUDController::OnLogClear);
		eventDispatcher->OnNextNPC.AddDynamic(this, &ADebugHUDController::OnNextNPC);
		eventDispatcher->OnPreviousNPC.AddDynamic(this, &ADebugHUDController::OnPreviousNPC);
		eventDispatcher->OnLogState.AddDynamic(this, &ADebugHUDController::OnLogState);
	}
}

void ADebugHUDController::OnEnableDebugMode(bool enable)
{
	if (mDebugHUDWidget->GetClass()->ImplementsInterface(UDebugHUD::StaticClass()))
	{
		IDebugHUD::Execute_OnEnableDebugMode(mDebugHUDWidget, enable);
	}
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnEnableDebugMode(mAgentDebugHUDWidget, enable);
	}
}

void ADebugHUDController::OnLogPredicate(const ANPCAIController* controller, int type, const FString& predicate)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogPredicate(mAgentDebugHUDWidget, controller, type, predicate);
	}
}

void ADebugHUDController::OnLogClear(const ANPCAIController* controller)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogClear(mAgentDebugHUDWidget, controller);
	}
}

void ADebugHUDController::OnNextNPC(const ANPCAIController* controller)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnNextNPC(mAgentDebugHUDWidget, controller);
	}
}

void ADebugHUDController::OnPreviousNPC(const ANPCAIController* controller)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnPreviousNPC(mAgentDebugHUDWidget, controller);
	}
}

void ADebugHUDController::OnLogState(const ANPCAIController* controller, const TArray<FString>& states)
{
	if (mAgentDebugHUDWidget->GetClass()->ImplementsInterface(UAgentDebugHUD::StaticClass()))
	{
		IAgentDebugHUD::Execute_OnLogState(mAgentDebugHUDWidget, controller, states);
	}
}
