#include "EscapeGoal.h"

#include "BountyHunter/Agents/AI/Actions/FindEscapePlaceAction.h"
#include "BountyHunter/Agents/AI/Predicates/FindEscapePlacePredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "goap/GoapUtils.h"
#include "goap/agent/IAgent.h"

EscapeGoal::EscapeGoal(IIEscapeComponent* component) :
mEscapeComponent{component}
{
}

void EscapeGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	mActions.push_back(CreateFindEscapePlaceAction());
}

void EscapeGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	mEscapeComponent->SetEscaping(false);
}

void EscapeGoal::DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	NAI::Goap::Utils::RemovePredicateWith(predicates, FIND_ESCAPE_PLACE_PREDICATE_NAME);
}

void EscapeGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
}

std::shared_ptr<NAI::Goap::IPredicate> EscapeGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	std::vector<std::shared_ptr<DangerStimulus>> stimulusList;
	
	utils::UtilsLibrary::FillWithStimulus<DangerStimulus>(memory, stimulusList, mAgent->GetPosition());
	if(!stimulusList.empty())
	{
		return std::make_shared<FindEscapePlacePredicate>(FIND_ESCAPE_PLACE_PREDICATE_ID, stimulusList);
	}
	else
	{
		return {};
	}
}

std::shared_ptr<FindEscapePlaceAction> EscapeGoal::CreateFindEscapePlaceAction() const
{
	std::vector<std::string> preConditions = {FIND_ESCAPE_PLACE_PREDICATE_NAME};
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {std::make_shared<NAI::Goap::BasePredicate>(EXPLORE_GOT_PATH_PREDICATE_ID, EXPLORE_GOT_PATH_PREDICATE_NAME)};

	auto action = std::make_shared<FindEscapePlaceAction>(preConditions, postConditions, 0, mAgent);

	return action;
}