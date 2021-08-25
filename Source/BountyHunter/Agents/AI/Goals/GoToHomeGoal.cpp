#include "GoToHomeGoal.h"

#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/Components/IHomeComponent.h"

#include "BountyHunter/utils/UtilsLibrary.h"

#include "goap/IPredicate.h"
#include "goap/predicates/PlaceIamPredicate.h"

#include "navigation/INavigationPath.h"
#include "navigation/INavigationPlanner.h"

#include <goap/GoapUtils.h>
#include <goap/sensory/IStimulus.h>
#include <glm/gtx/string_cast.hpp>

#include "BountyHunter/Stimulus/SoundStimulus.h"
#include "goap/BasePredicate.h"


GoToHomeGoal::GoToHomeGoal(IIHomeComponent* homeComponent,
                           const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
                           float precision) :
mHomeComponent { homeComponent },
mNavigationPlanner{navigationPlanner},
mPrecision{precision},
mLastReactedSoundId {0}
{
}

void GoToHomeGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	AddActions();
}

void GoToHomeGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	AddActions();
}

void GoToHomeGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	mHomeComponent->SetGoingHome(false);
	RemovePredicates(predicates);

	predicates.push_back(
		std::make_shared<NAI::Goap::PlaceIamPredicate>(
			NAI::Goap::PLACE_IAM_PREDICATE_ID,
			"PlaceIam",
			utils::UtilsLibrary::ConvertToString(mHomeComponent->GetHomeName())));
}

std::shared_ptr<NAI::Goap::IPredicate> GoToHomeGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	std::vector<std::shared_ptr<SoundStimulus>> orderedSoundStimulusList;

	FillWithOrderedSoundStimulus(memory, orderedSoundStimulusList);

	//TODO con la lista de sonidos ya podríamos saber si hay alguno peligroso
	//y entonces activar ir a home. En realidad esto lo haremos através del
	//escapeGoal. Este decidirá si hay que huir a home o no. Para probar, lo ponemos
	//aquí.
	/*
	if(orderedSoundStimulusList.empty())
	{
		return nullptr;
	}

	for(auto&& soundStimulus : orderedSoundStimulusList)
	{
		if(mLastReactedSoundId < soundStimulus->GetId())
		{
			mLastReactedSoundId = soundStimulus->GetId();
			return std::make_shared<NAI::Goap::BasePredicate>(GO_HOME_PREDICATE_ID, GO_HOME_PREDICATE_NAME);
		}
	}
	*/
	return nullptr;
}

void GoToHomeGoal::DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	mHomeComponent->SetGoingHome(false);
	RemovePredicates(predicates);
}

void GoToHomeGoal::AddActions()
{
	mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
}

void GoToHomeGoal::RemovePredicates(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) const
{
	NAI::Goap::Utils::RemovePredicateWith(predicates, NAI::Goap::PLACE_IAM_PREDICATE_NAME);
	NAI::Goap::Utils::RemovePredicateWith(predicates, GO_HOME_PREDICATE_NAME);
	NAI::Goap::Utils::RemovePredicateWith(predicates, HOME_PATH_PREDICATE_NAME);
}

void GoToHomeGoal::OnNavigationPath(const std::string& placeName, const std::shared_ptr<NAI::Navigation::INavigationPath>& path)
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

glm::vec3 GoToHomeGoal::GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const
{
	glm::vec3 destination(0.0f);
	const auto hasDestination = mNavigationPlanner->FillWithLocationGivenAName(
		utils::UtilsLibrary::ConvertToString(mHomeComponent->GetHomeName()),
		destination);

	check(hasDestination);
	
	return destination;
}

void GoToHomeGoal::FillWithOrderedSoundStimulus(const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory, std::vector<std::shared_ptr<SoundStimulus>>& soundStimulusList) const
{
	memory.PerformActionForEach(
        [this, &soundStimulusList](const std::shared_ptr<NAI::Goap::IStimulus> stimulus) -> bool
        {
            if(stimulus->GetClassName() == typeid(SoundStimulus).name())
            {
                const auto soundStimulus = std::static_pointer_cast<SoundStimulus>(stimulus);
            	//TODO mirar la categoría del sonido para saber si es peligroso o no por ejemplo.
            	//El SoundThreshold igual debería determinar la categoría.
                soundStimulusList.push_back(soundStimulus);
                return true;
            }
            return false;
        });

	std::sort(soundStimulusList.begin(), soundStimulusList.end(),
              [this](const std::shared_ptr<SoundStimulus>& a, const std::shared_ptr<SoundStimulus>& b)->bool
              {
                  //return glm::distance(a->GetPosition(), mAgent->GetPosition()) < glm::distance(b->GetPosition(), mAgent->GetPosition());
              	return a->GetId() < b->GetId();
              });
}

std::shared_ptr<NAI::Goap::FindPathToAction> GoToHomeGoal::CreateFindPathToAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner)
{
	std::vector<std::string> preConditions = {GO_HOME_PREDICATE_NAME};
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {std::make_shared<NAI::Goap::BasePredicate>(HOME_PATH_PREDICATE_ID, HOME_PATH_PREDICATE_NAME)};

	const auto goal = std::static_pointer_cast<GoToHomeGoal>(shared_from_this());
	auto action = std::make_shared<NAI::Goap::FindPathToAction>(goal, preConditions, postConditions, agent, navigationPlanner);

	return action;
}

std::shared_ptr<NAI::Goap::FollowPathAction> GoToHomeGoal::CreateFollowPathAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPath>& navigationPath) const
{
	std::vector<std::string> preConditions;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;
	preConditions.push_back(HOME_PATH_PREDICATE_NAME);
	
	auto action = std::make_shared<NAI::Goap::FollowPathAction>(preConditions, postConditions, agent, navigationPath, mPrecision);

	return action;
}
