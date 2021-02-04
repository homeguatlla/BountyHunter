﻿#include "EatGoal.h"
#include "BountyHunter/Agents/AI/Predicates/Predicates.h"
#include "BountyHunter/Agents/AI/Actions/EatAction.h"
#include "BountyHunter/Agents/AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Agents/AI/Predicates/ImHungryPredicate.h"
#include "BountyHunter/Stimulus/FoodStimulus.h"

#include <goap/GoapUtils.h>
#include <goap/IAction.h>
#include <goap/sensory/IStimulus.h>
#include <algorithm>


#include "goap/IPredicate.h"
#include "goap/PredicatesHandler.h"

EatGoal::EatGoal(UEatComponent* eatComponent) : mEatComponent { eatComponent }
{
}

void EatGoal::DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent)
{
	mAgent = agent;
	Reset();
}

void EatGoal::DoReset()
{
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
	std::vector<std::shared_ptr<FoodStimulus>> foodStimulusList;

	memory.PerformActionForEach(
		[&foodStimulusList](const std::shared_ptr<NAI::Goap::IStimulus> stimulus) -> bool
		{
			if(stimulus->GetClassName() == typeid(FoodStimulus).name())
			{
				const auto foodStimulus = std::static_pointer_cast<FoodStimulus>(stimulus);
				foodStimulusList.push_back(foodStimulus);
				return true;
			}
			return false;
		});
	if(foodStimulusList.empty())
	{
		return nullptr;
	}
	std::sort(foodStimulusList.begin(), foodStimulusList.end(),
            [this](const std::shared_ptr<FoodStimulus>& a, const std::shared_ptr<FoodStimulus>& b)->bool
            {
                return glm::distance(a->GetPosition(), mAgent->GetPosition()) < glm::distance(b->GetPosition(), mAgent->GetPosition());
            });
	
	return std::make_shared<FoodPredicate>(foodStimulusList[0]->GetPosition(), foodStimulusList[0]->GetAmount());
}

void EatGoal::AddActions()
{
	auto action = CreateEatAction();
	mActions.push_back(action);
}

std::shared_ptr<NAI::Goap::IAction> EatGoal::CreateEatAction()
{
	std::vector<std::string> preConditions = { FOOD_PREDICATE_NAME, IM_HUNGRY_PREDICATE_NAME };
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>> postConditions;

	unsigned int cost = 0;
	return std::make_shared<EatAction>(preConditions, postConditions, cost, mEatComponent);       
}
