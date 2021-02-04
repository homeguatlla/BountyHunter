#include "FoodThreshold.h"


#include "BountyHunter/Stimulus/FoodStimulus.h"
#include "goap/sensory/IStimulus.h"

bool FoodThreshold::IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	const auto foodStimulus = std::static_pointer_cast<FoodStimulus>(stimulus);
	return foodStimulus->GetAmount() > 0 && foodStimulus->IsActorAlive();
}
