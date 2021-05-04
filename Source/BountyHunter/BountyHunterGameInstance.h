// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Sound/SoundPlayer.h"
#include "BountyHunterGameInstance.generated.h"


UCLASS()
class BOUNTYHUNTER_API UBountyHunterGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void Init() override;
	void Shutdown() override;
	
	UFUNCTION(BlueprintPure, Category="Singleton")
	ASoundPlayer* GetSoundPlayer() const;
	
private:
	UPROPERTY()
	ASoundPlayer* mSoundPlayer;
};
