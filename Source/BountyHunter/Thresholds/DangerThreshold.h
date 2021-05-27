#pragma once
#include "goap/sensory/IThreshold.h"

class DangerThreshold : public NAI::Goap::IThreshold
{
public:
	DangerThreshold() = default;
	virtual ~DangerThreshold() = default;
	bool IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const override;
};
