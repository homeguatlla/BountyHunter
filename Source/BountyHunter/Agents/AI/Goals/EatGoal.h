#pragma once
#include <NAI/include/goap/BaseGoal.h>

#include "goap/agent/IAgent.h"

class EatGoal : public NAI::Goap::BaseGoal
{	
public:
	EatGoal() = default;
	virtual ~EatGoal() = default;

protected:
	void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	void DoReset() override;
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	void AddActions();
	std::shared_ptr<NAI::Goap::IAction> CreateEatAction();

private:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
};
