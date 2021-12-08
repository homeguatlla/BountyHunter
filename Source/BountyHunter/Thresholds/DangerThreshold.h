#pragma once
#include "glm/glm.hpp"
#include "goap/sensory/IThreshold.h"

class DangerThreshold : public NAI::Goap::IThreshold
{
public:
	DangerThreshold(float distanceThreshold);
	virtual ~DangerThreshold() = default;

	virtual bool IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const override;
	void SetDistanceThreshold(float distanceThreshold) { mDistanceThreshold = distanceThreshold; }
	void SetAgentPosition(const glm::vec3& position) { mAgentPosition = position; }
	
private:
	float mDistanceThreshold;
	glm::vec3 mAgentPosition;
};
