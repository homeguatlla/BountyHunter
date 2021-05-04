#include "SoundPlayer.h"


#include "BountyHunter/utils/UtilsLibrary.h"
#include "Kismet/GameplayStatics.h"

int ASoundPlayer::mSoundCounter = 0;

void ASoundPlayer::PlaySound(
	const UObject* WorldContextObject,
	USoundBase* Sound,
	FVector Location,
	float VolumeMultiplier,
	float PitchMultiplier,
	float StartTime,
	class USoundAttenuation* AttenuationSettings,
	USoundConcurrency* ConcurrencySettings)
{
	UGameplayStatics::PlaySoundAtLocation(
		WorldContextObject,
		Sound,
		Location,
		VolumeMultiplier,
		PitchMultiplier,
		StartTime,
		AttenuationSettings,
		ConcurrencySettings);

	const auto stimulus = std::make_shared<SoundStimulus>(mSoundCounter++, utils::UtilsLibrary::ConvertToVec3(Location));
	NotifyAll(stimulus);
}
