#pragma once
#include <memory>
#include <vector>
#include <NAI/include/goap/BaseGoal.h>


#include "BountyHunter/Stimulus/FoodStimulus.h"
#include "goap/agent/IAgent.h"

class IIEatComponent;

class EatGoal : public NAI::Goap::BaseGoal
{
public:
	EatGoal(IIEatComponent* eatComponent);
	virtual ~EatGoal() = default;
	unsigned GetCost() const override { return 10; } //TODO maybe 
	unsigned GetCost(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& inputPredicates, std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& accomplishedPredicates) const override { return 10; }	
	
protected:
	void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	std::vector<int> DoGetPredicatesIdsToRemove() const override;

	void DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	
	void AddActions();
	std::shared_ptr<NAI::Goap::IAction> CreateEatAction();

private:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	IIEatComponent* mEatComponent;
	mutable bool mHasFood;
	mutable bool mShouldRemoveFoodPredicate;
};
