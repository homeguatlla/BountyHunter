#include "DangerThreshold.h"

#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"

DangerThreshold::DangerThreshold(float distanceThreshold) : mDistanceThreshold {distanceThreshold}
{
}

bool DangerThreshold::IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	const auto dangerStimulus = std::static_pointer_cast<DangerStimulus>(stimulus);

	float distance = 0.0f;
	
	if(dangerStimulus->IsActorAlive())
	{
		distance = glm::distance(stimulus->GetPosition(), mAgentPosition);
	}
	
	return distance < mDistanceThreshold;
}
