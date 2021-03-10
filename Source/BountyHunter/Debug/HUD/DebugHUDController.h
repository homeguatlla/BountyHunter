// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <Blueprint/UserWidget.h>
//#include <BountyHunter/Debug/HUD/IDebugHUD.h>
#include "DebugHUDController.generated.h"

/**
 * Basic debug HUD
 */

class ANPCAIController;

UCLASS()
class BOUNTYHUNTER_API ADebugHUDController : public AActor
{
	GENERATED_BODY()

public:
	ADebugHUDController();

	void Initialize(int hudIndex, APlayerController* playerController, TArray<TSubclassOf<UUserWidget>> DebugHUDWidgetClasses);
	
	UFUNCTION()
	void OnEnableDebugMode(bool enable);
	UFUNCTION()
	void OnLogPredicate(const ANPCAIController* controller, int type, const FString& predicate);
	UFUNCTION()
	void OnLogClear(const ANPCAIController* controller);
	UFUNCTION()
	void OnNextNPC(const ANPCAIController* controller);
	UFUNCTION()
	void OnPreviousNPC(const ANPCAIController* controller);
	UFUNCTION()
	void OnLogState(const ANPCAIController* controller, const TArray<FString>& states);
	
private:
	void BindToDelegate();

public:
	UPROPERTY()
	UUserWidget* mDebugHUDWidget;

	UPROPERTY()
	UUserWidget* mAgentDebugHUDWidget;
};
