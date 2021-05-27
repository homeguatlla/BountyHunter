#pragma once
#include "BountyHunter/Agents/Components/IEscapeComponent.h"
#include "goap/BaseGoal.h"

class EscapeGoal : public NAI::Goap::BaseGoal
{
public:
	EscapeGoal(IIEscapeComponent* component);

protected:
	virtual void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	virtual void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual void DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;

private:
	IIEscapeComponent* mEscapeComponent;
};
