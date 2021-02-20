#include "NPCAgentFactory.h"
#include "NPCAgentBuilder.h"

#include "AI/NPCAgent.h"
#include "AI/NPCAIController.h"
#include "AI/Goals/EatGoal.h"

#include <goap/goals/GoToGoal.h>
#include <goap/planners/TreeGoapPlanner.h>
#include <goap/predicates/GoToPredicate.h>
#include <goap/sensory/IStimulus.h>
#include <goap/sensory/SensorySystem.h>

#include <BountyHunter/Stimulus/FoodStimulus.h>
#include <BountyHunter/Thresholds/FoodThreshold.h>


#include "AI/Predicates/Predicates.h"
#include "Components/EatComponent.h"
#include "GameFramework/Character.h"


NPCAgentFactory::NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner) :
mEventDispatcher{eventDispatcher},
mNavigationPlanner{planner}
{
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateAgent(
	NPCTypes type,
	ANPCAIController* controller,
	std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem)
{
	switch (type) {
	case Human:
		return CreateHuman(controller, sensorySystem);
	case Chicken:
	default:
		return CreateChicken(controller, sensorySystem);
	}
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateHuman(ANPCAIController* controller, std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const
{
	NPCAgentBuilder builder;
	
	auto acceptanceRadius = 100.0f;
	const auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner, acceptanceRadius);
	const auto predicate1 = std::make_shared<NAI::Goap::GoToPredicate>(GOTO_PREDICATE_ID, "GoTo", "GeneralStore");
	const auto predicate2 = std::make_shared<NAI::Goap::GoToPredicate>(GOTO_PREDICATE_ID + 1, "GoTo", "Saloon");
	return builder.WithController(controller)
                  .WithEventDispatcher(mEventDispatcher)
                  .WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
                  .WithGoal(goToGoal)
                  .WithPredicate(predicate1)
                  .WithPredicate(predicate2)
                  .Build<NPCAgent>();
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateChicken(ANPCAIController* controller, std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const
{
	NPCAgentBuilder builder;

	auto acceptanceRadius = 100.0f;
	return	builder.WithController(controller)
					.WithEventDispatcher(mEventDispatcher)
					.WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
					.WithGoal(std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner, acceptanceRadius))
					.WithPerceptionSystem(sensorySystem)
					.WithSensoryThreshold(typeid(FoodStimulus).name(), std::make_shared<FoodThreshold>())
                    .Build<NPCAgent>();
}