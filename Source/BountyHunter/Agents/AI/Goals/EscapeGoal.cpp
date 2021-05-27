#include "EscapeGoal.h"

EscapeGoal::EscapeGoal(IIEscapeComponent* component) :
mEscapeComponent{component}
{
}

void EscapeGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
}

void EscapeGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
}

void EscapeGoal::DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
}

void EscapeGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
}

std::shared_ptr<NAI::Goap::IPredicate> EscapeGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	//return std::make_shared<NAI::Goap::GoToPredicate>(GOTO_FOOD_PREDICATE_ID, "GoTo", foodStimulus->GetPosition());
	return {};
}
