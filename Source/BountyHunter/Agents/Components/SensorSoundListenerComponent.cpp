#include "SensorSoundListenerComponent.h"
#include "InteractableComponent.h"

#include <BountyHunter/utils/UtilsLibrary.h>
#include <BountyHunter/Agents/AI/NPCAIController.h>
#include <BountyHunter/BountyHunterGameInstance.h>

#include <goap/sensory/BaseSensor.h>


using namespace utils;

USensorSoundListenerComponent::USensorSoundListenerComponent()
{
	mSensor = std::make_shared<NAI::Goap::BaseSensor>();
}

void USensorSoundListenerComponent::BeginPlay()
{
	Super::BeginPlay();
	GetNPCAIController()->SubscribeSensor(mSensor);

	const auto gameInstance = Cast<UBountyHunterGameInstance>(GetWorld()->GetGameInstance());
	check(gameInstance);

	auto soundPlayer = gameInstance->GetSoundPlayer();
	soundPlayer->Subscribe(this);
}

void USensorSoundListenerComponent::OnNotification(std::shared_ptr<SoundStimulus> stimulus)
{
	mSensor->NotifyAll(stimulus);
}
