// Fill out your copyright notice in the Description page of Project Settings.


#include "BountyHunterGameInstance.h"

void UBountyHunterGameInstance::Init()
{
	Super::Init();

	mSoundPlayer = NewObject<ASoundPlayer>(this, FName("SoundPlayerSingleton"));
}

void UBountyHunterGameInstance::Shutdown()
{
	Super::Shutdown();

	if(IsValid(mSoundPlayer))
	{
		mSoundPlayer->Destroy();
	}
}

ASoundPlayer* UBountyHunterGameInstance::GetSoundPlayer() const
{
	return mSoundPlayer;
}
