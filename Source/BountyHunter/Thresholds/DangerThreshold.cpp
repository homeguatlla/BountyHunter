#include "DangerThreshold.h"

#include "BountyHunter/Stimulus/DangerStimulus.h"

bool DangerThreshold::IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	const auto foodStimulus = std::static_pointer_cast<DangerStimulus>(stimulus);
	return foodStimulus->IsActorAlive();
}
