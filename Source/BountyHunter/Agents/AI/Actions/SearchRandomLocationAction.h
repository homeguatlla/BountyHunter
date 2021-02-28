#pragma once
#include <goap/BaseAction.h>
#include "glm/glm.hpp"


class ExploreGoal;

namespace NAI {
	namespace Navigation {
		class INavigationPlanner;
	}
}

class IIExploreComponent;

namespace NAI {
	namespace Goap {
		class IAgent;
	}
}

class SearchRandomLocationAction : public NAI::Goap::BaseAction
{
public:
	SearchRandomLocationAction(const std::vector<std::string>& preConditions,
            const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
            unsigned int cost,
            const std::shared_ptr<ExploreGoal>& goal,
            const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
            const glm::vec3& center,
            float radius);
	virtual ~SearchRandomLocationAction() = default;

protected:
	void DoProcess(float elapsedTime) override;
private:
	std::shared_ptr<ExploreGoal> mGoal;
	std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
	glm::vec3 mCenter;
	float mRadius;
};
