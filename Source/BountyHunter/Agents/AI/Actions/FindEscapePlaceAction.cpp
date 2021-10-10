#include "FindEscapePlaceAction.h"

#include "BountyHunter/Agents/AI/Goals/EscapeGoal.h"
#include "BountyHunter/Agents/AI/Predicates/FindEscapePlacePredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "goap/agent/IAgent.h"

FindEscapePlaceAction::FindEscapePlaceAction(const std::shared_ptr<EscapeGoal>& goal,
											 const std::vector<std::string>& preConditions,
                                             const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                                             unsigned int cost,
                                             std::weak_ptr<NAI::Goap::IAgent> agent) :
BaseAction(preConditions, postConditions, cost),
mAgent{agent},
mGoal{goal}
{
	mHasAccomplished = false;
}

void FindEscapePlaceAction::DoProcess(float elapsedTime)
{
	if (auto agent = mAgent.lock())
	{
		const auto predicateMatch = GetPredicateMatchedPreconditionWithText(FIND_ESCAPE_PLACE_PREDICATE_NAME);
		const auto findEscapePredicate = std::static_pointer_cast<FindEscapePlacePredicate>(predicateMatch);
		glm::vec3 escapeDirection;
		
		findEscapePredicate->PerformActionForEachDangerousStimulus(
			[this, &agent, &escapeDirection](std::shared_ptr<DangerStimulus> dangerStimulus)
			{
				if(dangerStimulus->IsActorAlive())
				{
					//TODO revisar esto pues no parece correcto. Si la velocidad es 0 que debería ser el caso del test que estoy probando
					//tenemos que la velocidad es un vector del 0 a la posición actual que no tiene ningún sentido.
					
					const auto velocity = agent->GetPosition() - utils::UtilsLibrary::ConvertToVec3(dangerStimulus->GetActor()->GetVelocity());
					escapeDirection += velocity;
				}
			});
		mGoal->OnEscapeDirection(escapeDirection);
		mHasAccomplished = true;
	}
}
