#include "EatGoal.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/AI/Actions/EatAction.h"
#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Stimulus/FoodStimulus.h"
#include "goap/IPredicate.h"
#include "goap/predicates/GoToPredicate.h"

#include <goap/GoapUtils.h>
#include <goap/IAction.h>
#include <goap/sensory/IStimulus.h>

#include "BountyHunter/Agents/Components/IEatComponent.h"
#include "BountyHunter/utils/UtilsLibrary.h"

EatGoal::EatGoal(IIEatComponent* eatComponent) :
mEatComponent { eatComponent },
mHasFood {false},
mShouldRemoveFoodPredicate {false}
{
}

void EatGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	AddActions();
}

void EatGoal::DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	mHasFood = false;
	mShouldRemoveFoodPredicate = false;
	AddActions();
}

void EatGoal::DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	NAI::Goap::Utils::RemovePredicateWith(predicates, FOOD_PREDICATE_NAME);
	NAI::Goap::Utils::RemovePredicateWith(predicates, IM_HUNGRY_PREDICATE_NAME);
}

std::shared_ptr<NAI::Goap::IPredicate> EatGoal::DoTransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	if(!mEatComponent->HasHungry())
	{
		return nullptr;	
	}

	const auto foodStimulus = utils::UtilsLibrary::FindFirstStimulusAvailable<FoodStimulus>(memory, mAgent->GetPosition());

	if(foodStimulus == nullptr)
	{
		if(mHasFood)
		{
			mShouldRemoveFoodPredicate = true;
		}
		return nullptr;
	}
	
	const auto distance = glm::distance(foodStimulus->GetPosition(), mAgent->GetPosition());

	//UE_LOG(LogTemp, Log, TEXT("[EatGoal::DoTransformStimulusIntoPredicates] Stimulus id = %d distance = %f"), foodStimulusList[0]->GetId(), distance);

	mHasFood = true;
	
	if(distance < mEatComponent->GetMinDistanceToEat())
	{
		return std::make_shared<FoodPredicate>(
	        FOOD_PREDICATE_ID,
	        foodStimulus->GetPosition(),
	        foodStimulus->GetAmount(),
	        foodStimulus->GetActor());
	}
	else
	{
		return std::make_shared<NAI::Goap::GoToPredicate>(GOTO_FOOD_PREDICATE_ID, "GoTo", foodStimulus->GetPosition());
	}	
}

std::vector<int> EatGoal::DoGetPredicatesIdsToRemove() const
{
	if(mShouldRemoveFoodPredicate)
	{
		mShouldRemoveFoodPredicate = false;
		mHasFood = false;
		//We can be more specific here but it's ok. Instead of remove both predicates(could be possible only one of both remains in
		//the predicates list) we could remove only the one it's still present.
		UE_LOG(LogTemp, Warning, TEXT("EatGoal::DoGetPredicatesIdsToRemove"));
		return std::vector<int> {GOTO_FOOD_PREDICATE_ID, FOOD_PREDICATE_ID};
	}
	
	return {};
}

void EatGoal::DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	mEatComponent->Cancel();
}

void EatGoal::AddActions()
{
	const auto action = CreateEatAction();
	mActions.push_back(action);
}

std::shared_ptr<NAI::Goap::IAction> EatGoal::CreateEatAction()
{
	std::vector<std::string> preConditions = { FOOD_PREDICATE_NAME, IM_HUNGRY_PREDICATE_NAME };
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;

	unsigned int cost = 0;
	return std::make_shared<EatAction>(preConditions, postConditions, cost, mEatComponent);       
}