#include "ExploreGoal.h"

#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/AI/Actions/SearchRandomLocationAction.h"
#include "BountyHunter/Agents/Components/IExploreComponent.h"

#include "goap/IPredicate.h"
#include "goap/predicates/PlaceIamPredicate.h"

#include "navigation/INavigationPath.h"

#include <goap/GoapUtils.h>
#include <goap/IAction.h>
#include <goap/sensory/IStimulus.h>
#include <glm/gtx/string_cast.hpp>

ExploreGoal::ExploreGoal(IIExploreComponent* exploreComponent,
                         const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
                         float precision) :
mExploreComponent { exploreComponent },
mNavigationPlanner{navigationPlanner},
mPrecision{precision}
{
}

void ExploreGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	AddActions();
}

void ExploreGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	AddActions();
}

void ExploreGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	RemovePredicates(predicates);

	predicates.push_back(
		std::make_shared<NAI::Goap::PlaceIamPredicate>(
			NAI::Goap::PLACE_IAM_PREDICATE_ID,
			"PlaceIam",
			glm::to_string(mLocation)));
}

std::shared_ptr<NAI::Goap::IPredicate> ExploreGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	return nullptr;
}

void ExploreGoal::DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	RemovePredicates(predicates);
}

void ExploreGoal::AddActions()
{
	mActions.push_back(CreateExploreAction());
}

void ExploreGoal::RemovePredicates(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	NAI::Goap::Utils::RemovePredicateWith(predicates, EXPLORE_TO_PREDICATE_NAME);
	NAI::Goap::Utils::RemovePredicateWith(predicates, EXPLORE_GOT_PATH_PREDICATE_NAME);
	NAI::Goap::Utils::RemovePredicateWith(predicates, "PlaceIam");
}

void ExploreGoal::OnExploreLocation(const glm::vec3& location)
{
	mLocation = location;
	mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
}

void ExploreGoal::OnNavigationPath(const std::string& placeName, const std::shared_ptr<NAI::Navigation::INavigationPath>& path)
{
	if(!path->Empty())
	{
		mActions.push_back(CreateFollowPathAction(mAgent, path));
	}
	else
	{
		//TODO Cancel();
	}
}

glm::vec3 ExploreGoal::GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const
{
	return mLocation;
}

std::shared_ptr<NAI::Goap::IAction> ExploreGoal::CreateExploreAction()
{
	std::vector<std::string> preConditions = { EXPLORE_PREDICATE_NAME };
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {
		std::make_shared<NAI::Goap::BasePredicate>(EXPLORE_TO_PREDICATE_ID, EXPLORE_TO_PREDICATE_NAME)
    };
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

std::shared_ptr<NAI::Goap::FindPathToAction> ExploreGoal::CreateFindPathToAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner)
{
	std::vector<std::string> preConditions = {EXPLORE_TO_PREDICATE_NAME};
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {std::make_shared<NAI::Goap::BasePredicate>(EXPLORE_GOT_PATH_PREDICATE_ID, EXPLORE_GOT_PATH_PREDICATE_NAME)};

	const auto goal = std::static_pointer_cast<ExploreGoal>(shared_from_this());
	auto findPathTo = std::make_shared<NAI::Goap::FindPathToAction>(goal, preConditions, postConditions, agent, navigationPlanner);

	return findPathTo;
}

std::shared_ptr<NAI::Goap::FollowPathAction> ExploreGoal::CreateFollowPathAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPath>& navigationPath) const
{
	std::vector<std::string> preConditions;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;
	preConditions.push_back(EXPLORE_GOT_PATH_PREDICATE_NAME);

	auto followPathTo = std::make_shared<NAI::Goap::FollowPathAction>(preConditions, postConditions, agent, navigationPath, mPrecision);

	return followPathTo;
}
