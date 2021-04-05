#include "EatAction.h"
#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/Components/IEatComponent.h"
#include "BountyHunter/Agents/Components/InteractableComponent.h"
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
			const auto actor = foodPredicate->GetActor();
			auto interactableComponent = actor->FindComponentByClass<UInteractableComponent>();
			if(interactableComponent != nullptr && !interactableComponent->IsBeingUsed())
			{
				mEatComponent->Eat(foodPredicate->GetAmount());
				interactableComponent->Use();
				UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] HasHungry"));
			}
		}
	}
	else if(!mEatComponent->IsEating())
	{
		mHasAccomplished = true;
		const auto predicateMatch = GetPredicateMatchedPreconditionWithText(FOOD_PREDICATE_NAME);
		const auto foodPredicate = std::static_pointer_cast<FoodPredicate>(predicateMatch);

		auto actor = foodPredicate->GetActor();
		if(actor != nullptr && actor.IsValid())
		{
			actor->Destroy();
			UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] Food Actor destroyed"));
		}
		
		UE_LOG(LogTemp, Log, TEXT("[EatAction::DoProcess] Not eating -> accomplished"));
	}
}
