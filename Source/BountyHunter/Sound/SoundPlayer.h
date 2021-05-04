#pragma once

#include "ISoundPlayer.h"
#include "BountyHunter/Agents/Components/SensorSoundListenerComponent.h"
#include "BountyHunter/utils/subscriber/BasePublisher.h"

#include "SoundPlayer.generated.h"

UCLASS()
class ASoundPlayer : public AActor, public IISoundPlayer, public utils::subscriber::BasePublisher<SoundStimulus>
{
	GENERATED_BODY()

public:
	void PlaySound(const UObject* WorldContextObject, USoundBase* Sound, FVector Location, float VolumeMultiplier = 1.f, float PitchMultiplier = 1.f, float StartTime = 0.f, class USoundAttenuation* AttenuationSettings = nullptr, USoundConcurrency* ConcurrencySettings = nullptr) override;
	static int mSoundCounter;
};
