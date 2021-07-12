#pragma once
#include <goap/BaseAction.h>
#include <glm/glm.hpp>

namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

class FindEscapePlaceAction : public NAI::Goap::BaseAction
{
public:
	FindEscapePlaceAction(const std::vector<std::string>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost,
            std::weak_ptr<NAI::Goap::IAgent> agent);
	virtual ~FindEscapePlaceAction() override = default;

protected:
	void DoProcess(float elapsedTime) override;

private:
	glm::vec3 mEscapeDirection;
	std::weak_ptr<NAI::Goap::IAgent> mAgent;
};
