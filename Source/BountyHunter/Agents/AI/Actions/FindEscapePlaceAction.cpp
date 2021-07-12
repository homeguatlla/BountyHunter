#include "FindEscapePlaceAction.h"

#include "BountyHunter/Agents/AI/Predicates/FindEscapePlacePredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"
#include "goap/agent/IAgent.h"

FindEscapePlaceAction::FindEscapePlaceAction(const std::vector<std::string>& preConditions,
                                             const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                                             unsigned int cost,
                                             std::weak_ptr<NAI::Goap::IAgent> agent) :
BaseAction(preConditions, postConditions, cost),
mAgent{agent}
{
	mHasAccomplished = false;
}

void FindEscapePlaceAction::DoProcess(float elapsedTime)
{
	if (auto agent = mAgent.lock())
	{
		const auto predicateMatch = GetPredicateMatchedPreconditionWithText(FIND_ESCAPE_PLACE_PREDICATE_NAME);
		const auto findEscapePredicate = std::static_pointer_cast<FindEscapePlacePredicate>(predicateMatch);

		findEscapePredicate->PerformActionForEachDangerousStimulus(
			[this, &agent](std::shared_ptr<DangerStimulus> dangerStimulus)
			{
				if(dangerStimulus->IsActorAlive())
				{
					const auto velocity = agent->GetPosition() - utils::UtilsLibrary::ConvertToVec3(dangerStimulus->GetActor()->GetVelocity());
					mEscapeDirection += velocity;
				}
			});

		mHasAccomplished = true;
	}
}
