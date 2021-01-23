#include "EatAction.h"

EatAction::EatAction(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& preConditions,
	const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions, unsigned cost) :
BaseAction(preConditions, postConditions, cost)
{
	mHasAccomplished = false;
}

void EatAction::DoProcess(float elapsedTime)
{
}
