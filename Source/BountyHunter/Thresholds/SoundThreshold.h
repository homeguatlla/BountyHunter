#pragma once
#include "goap/sensory/IThreshold.h"

class SoundThreshold : public NAI::Goap::IThreshold
{
public:
	SoundThreshold() = default;
	virtual ~SoundThreshold() = default;
	bool IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const override;
};
