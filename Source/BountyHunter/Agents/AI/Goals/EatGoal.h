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

protected:
	void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	std::vector<int> DoGetPredicatesIdsToRemove() const override;
	
	void AddActions();
	std::shared_ptr<NAI::Goap::IAction> CreateEatAction();

private:
	std::shared_ptr<FoodStimulus> FindFirstFoodStimulusAvailable(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const;
	void FillWithFoodStimulus(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory,
		std::vector<std::shared_ptr<FoodStimulus>>& foodStimulusList) const;

	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	IIEatComponent* mEatComponent;
	mutable bool mHasFood;
	mutable bool mShouldRemoveFoodPredicate;
};
