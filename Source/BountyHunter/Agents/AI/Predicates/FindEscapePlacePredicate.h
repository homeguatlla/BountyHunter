#pragma once

#include <functional>

#include "goap/sensory/IStimulus.h"
#include "goap/BasePredicate.h"
#include <vector>

class DangerStimulus;

class FindEscapePlacePredicate : public NAI::Goap::BasePredicate
{
public:
	FindEscapePlacePredicate(int id, std::vector<std::shared_ptr<DangerStimulus>> stimulusList);
	virtual ~FindEscapePlacePredicate() override = default;

	void PerformActionForEachDangerousStimulus(std::function<void(std::shared_ptr<DangerStimulus> dangerStimulus)> action);

private:
	std::vector<std::shared_ptr<DangerStimulus>> mStimulusList;
};
