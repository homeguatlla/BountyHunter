#include "WaitAction.h"

WaitAction::WaitAction(const std::vector<std::string>& preConditions,
                     const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                     unsigned int cost, float time) :
BaseAction(preConditions, postConditions, cost),
mTimeToWait{time}
{
	mHasAccomplished = false;
}

void WaitAction::DoProcess(float elapsedTime)
{
	mTimeToWait -= elapsedTime;

	if(mTimeToWait <= 0.0f)
	{
		mHasAccomplished = true;
	}
}