// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPCAgentComponent.h"
#include <goap/sensory/BaseSensor.h>
#include "BountyHunter/Stimulus/SoundStimulus.h"
#include "BountyHunter/utils/subscriber/ISubscriber.h"

#include "SensorSoundListenerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API USensorSoundListenerComponent :	public UNPCAgentComponent,
														public utils::subscriber::ISubscriber<SoundStimulus>
{
	GENERATED_BODY()

public:
	USensorSoundListenerComponent();

	/** If true, draw debug lines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound Listener Attributes")
	bool IsDebug;

	void BeginPlay() override;
	void OnNotification(std::shared_ptr<SoundStimulus> stimulus) override;
	
private:
	std::shared_ptr<NAI::Goap::BaseSensor> mSensor;
};
