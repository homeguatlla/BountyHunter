#pragma once
#include <goap/BaseAction.h>

class EatAction : public NAI::Goap::BaseAction
{
public:
	EatAction(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost);
	virtual ~EatAction() = default;

protected:
	void DoProcess(float elapsedTime) override;	
};
