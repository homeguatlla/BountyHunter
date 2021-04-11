#pragma once
#include "goap/BaseAction.h"

class WaitAction : public NAI::Goap::BaseAction
{
public:
	WaitAction(const std::vector<std::string>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost, float maxWaitingTime, float minWaitingTime);
	virtual ~WaitAction() = default;

protected:
	void DoProcess(float elapsedTime) override;

private:
	const float mMaxWaitingTime;
	const float mMinWaitingTime;
	float mTimeToWait;
};

