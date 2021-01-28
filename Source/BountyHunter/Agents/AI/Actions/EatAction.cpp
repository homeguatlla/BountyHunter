#include "EatAction.h"

#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Agents/Components/EatComponent.h"

EatAction::EatAction(const std::vector<std::string>& preConditions,
                     const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                     unsigned int cost,
                     UEatComponent* eatComponent) :
BaseAction(preConditions, postConditions, cost),
mEatComponent{eatComponent}
{
	mHasAccomplished = false;
}

void EatAction::DoProcess(float elapsedTime)
{
	if(mEatComponent->HasHungry())
	{	
		const auto predicateMatch = GetPredicateMatchedPreconditionWithIndex(0);
		const auto foodPredicate = std::static_pointer_cast<FoodPredicate>(predicateMatch);
		mEatComponent->Eat(foodPredicate->GetAmount());
	}
	else if(!mEatComponent->IsEating())
	{
		mHasAccomplished = true;
	}
}
