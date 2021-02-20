﻿#pragma once
#include <goap/BaseAction.h>

class IIEatComponent;

namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

class EatAction : public NAI::Goap::BaseAction
{
public:
	EatAction(const std::vector<std::string>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost,
            IIEatComponent* eatComponent);
	virtual ~EatAction() = default;

protected:
	void DoProcess(float elapsedTime) override;

private:
	IIEatComponent* mEatComponent;
};
