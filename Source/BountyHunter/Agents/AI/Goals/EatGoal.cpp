#include "EatGoal.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include <goap/GoapUtils.h>

#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"


void EatGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	NAI::Goap::Utils::RemovePredicateWith(predicates, FOOD_PREDICATE);
}

std::shared_ptr<NAI::Goap::IPredicate> EatGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	return nullptr;
}
