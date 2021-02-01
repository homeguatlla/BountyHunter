﻿#include "NPCAgentFactory.h"
#include "NPCAgentBuilder.h"

#include "AI/NPCAgent.h"
#include "AI/NPCAIController.h"
#include "AI/Goals/EatGoal.h"

#include <goap/goals/GoToGoal.h>
#include <goap/planners/TreeGoapPlanner.h>
#include <goap/predicates/GoToPredicate.h>

#include "AI/Predicates/FoodPredicate.h"
#include "BountyHunter/Stimulus/FoodStimulus.h"
#include "BountyHunter/Thresholds/FoodThreshold.h"
#include "Components/EatComponent.h"
#include "GameFramework/Character.h"
#include "goap/sensory/IStimulus.h"
#include "goap/sensory/PerceptionSystem.h"
#include "goap/sensory/SensorySystem.h"

NPCAgentFactory::NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner) :
mEventDispatcher{eventDispatcher},
mNavigationPlanner{planner}
{
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateAgent(
	NPCTypes type,
	ANPCAIController* controller)
{
	switch (type) {
	case Human:
		return CreateHuman(controller);
	case Chicken:
	default:
		return CreateChicken(controller);
	}
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateHuman(ANPCAIController* controller) const
{
	NPCAgentBuilder builder;
	
	auto acceptanceRadius = 100.0f;
	const auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner, acceptanceRadius);
	const auto predicate1 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "GeneralStore");
	const auto predicate2 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "Saloon");
	return builder.WithController(controller)
                  .WithEventDispatcher(mEventDispatcher)
                  .WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
                  .WithGoal(goToGoal)
                  .WithPredicate(predicate1)
                  .WithPredicate(predicate2)
                  .Build<NPCAgent>();
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateChicken(ANPCAIController* controller) const
{
	NPCAgentBuilder builder;

	const auto character = controller->GetCharacter();
	auto eatComponent = character->FindComponentByClass<UEatComponent>();
	assert(eatComponent != nullptr);

	auto sensorySystem = std::make_shared<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>>();
	
	//el VisionComponent debe heredar de BaseSensor
	//El SensorySystem se tiene que suscribir a VisionComponent
	return	builder.WithController(controller)
					.WithEventDispatcher(mEventDispatcher)
					.WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
					.WithGoal(std::make_shared<EatGoal>(eatComponent))
					.WithPredicate(std::make_shared<FoodPredicate>(glm::vec3(0.0f), 1))
					.WithPerceptionSystem(sensorySystem)
					.WithSensoryThreshold(typeid(FoodStimulus).name(), std::make_shared<FoodThreshold>())
                    .Build<NPCAgent>();
}