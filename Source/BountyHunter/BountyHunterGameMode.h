// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include <BountyHunter/EventDispatcher.h>
#include "BountyHunterGameMode.generated.h"

const float NavigationPointsPrecision = 100.0f;

UCLASS(minimalapi)
class ABountyHunterGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABountyHunterGameMode();
	AEventDispatcher* GetEventDispatcher() { return mEventDispatcher; }

	/** Blueprint class which manage events with HUD */
	UPROPERTY(EditAnywhere, Category = "HUD Event Dispatcher")
		TSubclassOf<AEventDispatcher> HUDEventDispatcherClass;

protected:
	void BeginPlay() override;

private:
	AEventDispatcher* mEventDispatcher;
};



