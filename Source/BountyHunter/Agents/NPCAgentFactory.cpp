﻿#include "NPCAgentFactory.h"
#include "NPCAgentBuilder.h"

#include "AI/NPCAgent.h"
#include "AI/NPCAIController.h"

#include "goap/agent/AgentBuilder.h"
#include "goap/goals/GoToGoal.h"
#include "goap/planners/TreeGoapPlanner.h"
#include "goap/predicates/GoToPredicate.h"


NPCAgentFactory::NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner) :
mEventDispatcher{eventDispatcher},
mNavigationPlanner{planner}
{
}

std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateAgent(
	NPCTypes type,
	ANPCAIController* controller)
{
	NPCAgentBuilder builder;
	
	switch (type) {
	case Human:
		{
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
	case Chicken:
	default:
		return builder.WithController(controller)
                      .WithEventDispatcher(mEventDispatcher)
					  .WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
                      .Build<NPCAgent>();
	}
}
