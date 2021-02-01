#pragma once
#include "goap/sensory/IThreshold.h"

class FoodThreshold : public NAI::Goap::IThreshold
{
public:
	FoodThreshold() = default;
	virtual ~FoodThreshold() = default;
	bool IsStimulusPerceived(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const override;
};
