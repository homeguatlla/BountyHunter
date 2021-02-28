#include "ExploreGoal.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/AI/Actions/SearchRandomLocationAction.h"
#include "goap/IPredicate.h"

#include <goap/GoapUtils.h>
#include <goap/IAction.h>
#include <goap/sensory/IStimulus.h>

#include "BountyHunter/Agents/Components/IExploreComponent.h"
#include "goap/predicates/GoToPredicate.h"

ExploreGoal::ExploreGoal(IIExploreComponent* exploreComponent,
                         const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
                         float precision) :
GoToGoal(navigationPlanner, precision),
mExploreComponent { exploreComponent },
mNavigationPlanner{navigationPlanner}
{
}

void ExploreGoal::OnExploreLocation(const glm::vec3& location)
{
	mAgent->OnNewPredicate(std::make_shared<NAI::Goap::GoToPredicate>(GOTO_PREDICATE_ID, GOTO_PREDICATE_NAME, location));
}

void ExploreGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	AddActions();
	GoToGoal::DoCreate(agent);
}

void ExploreGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	AddActions();
	GoToGoal::DoReset(predicates);
}

void ExploreGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	GoToGoal::DoAccomplished(predicates);
}

std::shared_ptr<NAI::Goap::IPredicate> ExploreGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	return nullptr;
}

void ExploreGoal::AddActions()
{
	mActions.push_back(CreateExploreAction());
}

std::shared_ptr<NAI::Goap::IAction> ExploreGoal::CreateExploreAction()
{
	std::vector<std::string> preConditions = { EXPLORE_PREDICATE_NAME };
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;
	const auto goal = std::static_pointer_cast<ExploreGoal>(shared_from_this());
	unsigned int cost = 100;
	
	return std::make_shared<SearchRandomLocationAction>(
		preConditions,
		postConditions,
		cost,
		goal,
		mNavigationPlanner,
		mAgent->GetPosition(),
		mExploreComponent->GetExplorationRadius());       
}
