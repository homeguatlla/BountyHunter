#include "EatAction.h"
#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/Components/IEatComponent.h"
#include "GameFramework/Actor.h"

EatAction::EatAction(const std::vector<std::string>& preConditions,
                     const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& postConditions,
                     unsigned int cost,
                     IIEatComponent* eatComponent) :
BaseAction(preConditions, postConditions, cost),
mEatComponent{eatComponent}
{
	mHasAccomplished = false;
}

void EatAction::DoProcess(float elapsedTime)
{
	if(mEatComponent->HasHungry())
	{	
		const auto predicateMatch = GetPredicateMatchedPreconditionWithText(FOOD_PREDICATE_NAME);
		const auto foodPredicate = std::static_pointer_cast<FoodPredicate>(predicateMatch);
		if(foodPredicate->IsActorAlive())
		{
			mEatComponent->Eat(foodPredicate->GetAmount());
			UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] HasHungry"));
		}
	}
	else if(!mEatComponent->IsEating())
	{
		mHasAccomplished = true;
		const auto predicateMatch = GetPredicateMatchedPreconditionWithText(FOOD_PREDICATE_NAME);
		const auto foodPredicate = std::static_pointer_cast<FoodPredicate>(predicateMatch);
		
		foodPredicate->GetActor()->Destroy();
		UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] Food Actor destroyed"));
		UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] Not eating -> accomplished"));
	}
}
