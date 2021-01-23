#pragma once
#include <NAI/include/goap/BaseGoal.h>

#include "goap/agent/IAgent.h"

class EatGoal : public NAI::Goap::BaseGoal
{

protected:
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
public:
	EatGoal() = default;
	virtual ~EatGoal() = default;
};
