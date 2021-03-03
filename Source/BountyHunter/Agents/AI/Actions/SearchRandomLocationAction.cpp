#include "SearchRandomLocationAction.h"
#include "BountyHunter/Agents/AI/Goals/ExploreGoal.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "navigation/INavigationPlanner.h"

SearchRandomLocationAction::SearchRandomLocationAction(const std::vector<std::string>& preConditions,
                                                       const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                                                       unsigned int cost,
                                                       const std::shared_ptr<ExploreGoal>& goal,
                                                       const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
                                                       const glm::vec3& center,
                                                       float radius) :
BaseAction(preConditions, postConditions, cost),
mGoal{goal},
mNavigationPlanner{navigationPlanner},
mCenter{center},
mRadius{radius}
{
	mHasAccomplished = false;
}

void SearchRandomLocationAction::DoProcess(float elapsedTime)
{
	//TODO hay que hacer esto varias veces si no encuentra una posición.
	glm::vec3 location;
	const auto result = mNavigationPlanner->GetRandomReachablePointInRadius(mCenter, mRadius, location);
	if(result)
	{
		mGoal->OnExploreLocation(location);
		mHasAccomplished = true;
	}
}
