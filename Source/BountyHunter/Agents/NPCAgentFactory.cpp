﻿#include "NPCAgentFactory.h"
#include "NPCAgentBuilder.h"

#include "AI/NPCAgent.h"
#include "AI/NPCAIController.h"
#include "AI/Goals/EatGoal.h"

#include <goap/BasePredicate.h>
#include <goap/goals/GoToGoal.h>
#include <goap/planners/TreeGoapPlanner.h>
#include <goap/predicates/GoToPredicate.h>
#include <goap/sensory/IStimulus.h>
#include <goap/sensory/SensorySystem.h>

#include <BountyHunter/Stimulus/FoodStimulus.h>
#include <BountyHunter/Stimulus/SoundStimulus.h>
#include <BountyHunter/Stimulus/DangerStimulus.h>

#include <BountyHunter/Thresholds/FoodThreshold.h>
#include <BountyHunter/Thresholds/DangerThreshold.h>
#include <BountyHunter/Thresholds/SoundThreshold.h>

#include <BountyHunter/Agents/AI/Predicates/Predicates.h>
#include <BountyHunter/Agents/FSM/Chicken/ChickenContext.h>
#include <BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h>

#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

#include <BountyHunter/FSM/StatesMachineFactory.h>

namespace TLN
{
	NPCAgentFactory::NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner) :
 mEventDispatcher{eventDispatcher},
 mNavigationPlanner{planner}
	{
	}

	std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateAgent(
        NPCTypes type,
        ANPCAIController* controller,
        INPCCharacter* character,
        std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem)
	{
		switch (type) {
		case NPCTypes::Human:
			return CreateHuman(controller, character, sensorySystem);
		case NPCTypes::Chicken:
		default:
            return CreateChicken(controller, character, sensorySystem);
		}
	}

	std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateHuman(
        ANPCAIController* controller,
        INPCCharacter* character,
        std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const
	{
		NPCAgentBuilder<
            NPCAgent<CharacterState, CharacterContext>,
            CharacterState,
            CharacterContext> builder;
	
		auto acceptanceRadius = 100.0f;
		const auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner, acceptanceRadius);
		const auto predicate1 = std::make_shared<NAI::Goap::GoToPredicate>(GOTO_PREDICATE_ID, NAI::Goap::PREDICATE_GO_TO_NAME, "GeneralStore");
		const auto predicate2 = std::make_shared<NAI::Goap::GoToPredicate>(GOTO_PREDICATE_ID + 1, NAI::Goap::PREDICATE_GO_TO_NAME, "Saloon");
		return builder.WithController(controller)
                      .WithEventDispatcher(mEventDispatcher)
                      .WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
                      .WithGoal(goToGoal)
                      .WithPredicate(predicate1)
                      .WithPredicate(predicate2)
                      .Build();
	}

	std::shared_ptr<NAI::Goap::IAgent> NPCAgentFactory::CreateChicken(
        ANPCAIController* controller,
        INPCCharacter* character,
        std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const
	{
		NPCAgentBuilder<
            NPCAgent<Chicken::ChickenState, Chicken::ChickenContext>,
            Chicken::ChickenState,
            Chicken::ChickenContext> builder;

		StatesMachineFactory fsmFactory;
	
		auto acceptanceRadius = 100.0f;
		return	builder.WithController(controller)
                        .WithEventDispatcher(mEventDispatcher)
                        .WithGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
                        .WithGoal(std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner, acceptanceRadius))
						.WithPredicate(std::make_shared<NAI::Goap::BasePredicate>(EXPLORE_PREDICATE_ID, EXPLORE_PREDICATE_NAME))
                        .WithPerceptionSystem(sensorySystem)
                        .WithSensoryThreshold(typeid(FoodStimulus).name(), std::make_shared<FoodThreshold>())
						.WithSensoryThreshold(typeid(SoundStimulus).name(), std::make_shared<SoundThreshold>())
						.WithSensoryThreshold(typeid(DangerStimulus).name(), std::make_shared<DangerThreshold>())
                        .WithStatesMachine(
                            fsmFactory.CreateChicken(
                                FSMType::CHICKEN_MOVEMENT,
                                std::make_shared<Chicken::ChickenContext>(
                                    controller->GetWorld(),
                                    character)))
						.WithStatesMachine(
							fsmFactory.CreateChicken(
								FSMType::CHICKEN_STATE,
								std::make_shared<Chicken::ChickenContext>(
				                    controller->GetWorld(),
				                    character)))
                        .Build();
	}
}
