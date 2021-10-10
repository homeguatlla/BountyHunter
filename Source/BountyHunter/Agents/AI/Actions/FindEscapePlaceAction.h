#pragma once
#include <goap/BaseAction.h>
#include <glm/glm.hpp>

class EscapeGoal;

namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

//TODO hay que ver esto, ahora mismo devuelve la dirección de fuga y por tanto no el place
class FindEscapePlaceAction : public NAI::Goap::BaseAction
{
public:
	FindEscapePlaceAction(
			const std::shared_ptr<EscapeGoal>& goal,
			const std::vector<std::string>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost,
            std::weak_ptr<NAI::Goap::IAgent> agent);
	virtual ~FindEscapePlaceAction() override = default;

protected:
	virtual void DoProcess(float elapsedTime) override;

private:
	std::weak_ptr<NAI::Goap::IAgent> mAgent;
	std::shared_ptr<EscapeGoal> mGoal;
};
