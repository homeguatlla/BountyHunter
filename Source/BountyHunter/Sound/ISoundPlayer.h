#pragma once
#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ISoundPlayer.generated.h"

UINTERFACE(Blueprintable, meta = (CannotImplementInterfaceInBlueprint))
class UISoundPlayer : public UInterface
{
	GENERATED_BODY()
};

class IISoundPlayer
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category = "Sound Player")
    virtual void PlaySound(
    	const UObject* WorldContextObject,
    	USoundBase* Sound,
    	FVector Location,
    	float VolumeMultiplier = 1.f, 
		float PitchMultiplier = 1.f,
		float StartTime = 0.f,
		class USoundAttenuation* AttenuationSettings = nullptr,
		USoundConcurrency* ConcurrencySettings = nullptr) = 0;
};