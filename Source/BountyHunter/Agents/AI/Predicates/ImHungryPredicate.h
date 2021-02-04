#pragma once
#include <goap/BasePredicate.h>


namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

class ImHungryPredicate : public NAI::Goap::BasePredicate
{
public:
	ImHungryPredicate(int id);
	virtual ~ImHungryPredicate() = default;

	bool HasHungry(std::shared_ptr<NAI::Goap::IAgent> agent) const;
};
