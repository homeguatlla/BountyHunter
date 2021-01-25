#pragma once
#include <goap/BaseAction.h>

class UEatComponent;

namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

class EatAction : public NAI::Goap::BaseAction
{
public:
	EatAction(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost,
            UEatComponent* eatComponent);
	virtual ~EatAction() = default;

protected:
	void DoProcess(float elapsedTime) override;

private:
	UEatComponent* mEatComponent;
};
