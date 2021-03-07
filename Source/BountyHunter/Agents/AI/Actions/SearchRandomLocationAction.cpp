#include "SearchRandomLocationAction.h"
#include "BountyHunter/Agents/AI/Goals/ExploreGoal.h"
#include "BountyHunter/Agents/Components/IExploreComponent.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "navigation/INavigationPlanner.h"

SearchRandomLocationAction::SearchRandomLocationAction(const std::vector<std::string>& preConditions,
                                                       const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                                                       unsigned int cost,
                                                       const std::shared_ptr<ExploreGoal>& goal,
                                                       const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
                                                       IIExploreComponent* exploreComponent,
                                                       const glm::vec3& center) :
BaseAction(preConditions, postConditions, cost),
mGoal{goal},
mNavigationPlanner{navigationPlanner},
mExploreComponent { exploreComponent },
mCenter{center}
{
	mHasAccomplished = false;
}

void SearchRandomLocationAction::DoProcess(float elapsedTime)
{
	mExploreComponent->SetExplore(true);
	
	//Si no encuentra una posición, en el próximo DoProcess volverá a probar.
	glm::vec3 location;
	const auto result = mNavigationPlanner->GetRandomReachablePointInRadius(mCenter, mExploreComponent->GetExplorationRadius(), location);
	if(result)
	{
		mGoal->OnExploreLocation(location);
		mHasAccomplished = true;
	}
}
