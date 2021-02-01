#include "FoodThreshold.h"

#include "goap/sensory/IStimulus.h"

bool FoodThreshold::IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	return true;
}
