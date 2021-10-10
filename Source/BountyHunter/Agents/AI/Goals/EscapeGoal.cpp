#include "EscapeGoal.h"

#include "BountyHunter/Agents/AI/Actions/FindEscapePlaceAction.h"
#include "BountyHunter/Agents/AI/Predicates/FindEscapePlacePredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "goap/GoapUtils.h"
#include "goap/actions/FindPathToAction.h"
#include "goap/agent/IAgent.h"
#include "navigation/INavigationPath.h"

EscapeGoal::EscapeGoal(
	IIEscapeComponent* component,
	const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
	float precision) :
mEscapeComponent{component},
mNavigationPlanner{navigationPlanner},
mEscapeDirection{0.0f},
mPrecision{precision}
{
}

void EscapeGoal::OnNavigationPath(const std::string& placeName,
	const std::shared_ptr<NAI::Navigation::INavigationPath>& path)
{
	//TODO dibujar el path para saber que posicion tiene que ir.
	if(!path->Empty())
	{
		mActions.push_back(CreateFollowPathAction(mAgent, path));
		
	}
	else
	{
		//TODO Cancel();
	}
}

glm::vec3 EscapeGoal::GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const
{
	return mEscapeDirection;
}

void EscapeGoal::OnEscapeDirection(const glm::vec3& direction)
{
	mEscapeDirection = direction;
	//TODO hay que pensar quién resuelve esto, pero para calcular un path hay que
	//calcular un destino y solo tenemos una dirección
	//Quizá lo que habría que hacer es simplemente calcular una posición a una cierta distancia.
	//si esta posición es alcanzable pues se va hasta allí. Y una vez llegue se valida si todavía hace falta
	//seguir huyendo. Pensar ahora el estádo pánico para terminar esto.
	mActions.push_back(CreateFindPathToAction(mAgent, mNavigationPlanner));
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

std::shared_ptr<FindEscapePlaceAction> EscapeGoal::CreateFindEscapePlaceAction()
{
	std::vector<std::string> preConditions = {FIND_ESCAPE_PLACE_PREDICATE_NAME};
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {std::make_shared<NAI::Goap::BasePredicate>(ESCAPE_PREDICATE_ID, ESCAPE_PREDICATE_NAME)};

	const auto goal = std::static_pointer_cast<EscapeGoal>(shared_from_this());
	
	auto action = std::make_shared<FindEscapePlaceAction>(goal, preConditions, postConditions, 0, mAgent);

	return action;
}

std::shared_ptr<NAI::Goap::FindPathToAction> EscapeGoal::CreateFindPathToAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner)
{
	std::vector<std::string> preConditions = {ESCAPE_PREDICATE_NAME};
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions = {std::make_shared<NAI::Goap::BasePredicate>(ESCAPE_GOT_PATH_PREDICATE_ID, ESCAPE_GOT_PATH_PREDICATE_NAME)};

	const auto goal = std::static_pointer_cast<EscapeGoal>(shared_from_this());
	auto action = std::make_shared<NAI::Goap::FindPathToAction>(goal, preConditions, postConditions, agent, navigationPlanner);

	return action;
}

std::shared_ptr<NAI::Goap::FollowPathAction> EscapeGoal::CreateFollowPathAction(const std::weak_ptr<NAI::Goap::IAgent>& agent, const std::shared_ptr<NAI::Navigation::INavigationPath>& navigationPath) const
{
	std::vector<std::string> preConditions;
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;
	preConditions.push_back(ESCAPE_GOT_PATH_PREDICATE_NAME);
	
	auto action = std::make_shared<NAI::Goap::FollowPathAction>(preConditions, postConditions, agent, navigationPath, mPrecision);

	return action;
}