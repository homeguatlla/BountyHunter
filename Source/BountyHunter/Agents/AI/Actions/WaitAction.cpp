#include "WaitAction.h"

#include "BountyHunter/utils/UtilsLibrary.h"

WaitAction::WaitAction(const std::vector<std::string>& preConditions,
                       const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                       unsigned int cost, float maxWaitingTime, float minWaitingTime) :
BaseAction(preConditions, postConditions, cost),
mMaxWaitingTime { maxWaitingTime },
mMinWaitingTime { minWaitingTime }
{
	mHasAccomplished = false;
	mTimeToWait = utils::UtilsLibrary::GetRandomRange(minWaitingTime, maxWaitingTime);
}

void WaitAction::DoProcess(float elapsedTime)
{
	mTimeToWait -= elapsedTime;

	if(mTimeToWait <= 0.0f)
	{
		mHasAccomplished = true;
	}
}