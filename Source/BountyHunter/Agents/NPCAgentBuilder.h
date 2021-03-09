#pragma once
#include <vector>
#include <memory>
#include <BountyHunter/Agents/AI/NPCAgentDebugDecorator.h>

#include "goap/agent/AgentBuilder.h"
#include "goap/sensory/PerceptionSystem.h"
#include "utils/fsm/StatesMachine.h"

class IAgentAIController;
class AEventDispatcher;
class ANPCAIController;

namespace NAI {
	namespace Goap {
		class IGoapPlanner;
		class IGoal;
		class IPredicate;
		class IAgent;
	}
}


namespace TLN
{
template<class TAgent, typename TStateID, class TContext>
 class NPCAgentBuilder : public NAI::Goap::AgentBuilder
	{
	public:
		NPCAgentBuilder() = default;
	
		NPCAgentBuilder& WithController(ANPCAIController* controller);
		NPCAgentBuilder& WithEventDispatcher(AEventDispatcher* eventDispatcher);

		NPCAgentBuilder& WithGoal(std::shared_ptr<NAI::Goap::IGoal> goal);
		NPCAgentBuilder& WithPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate);
		NPCAgentBuilder& WithGoapPlanner(std::shared_ptr<NAI::Goap::IGoapPlanner> planner);
		NPCAgentBuilder& WithSensoryThreshold(const std::string& stimulusClassName, std::shared_ptr<NAI::Goap::IThreshold> threshold);
		NPCAgentBuilder& WithPerceptionSystem(std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem);
		NPCAgentBuilder& WithStatesMachine(std::shared_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> machine);
		std::shared_ptr<NAI::Goap::IAgent> Build();

	private:
		ANPCAIController* mController;
		AEventDispatcher* mEventDispatcher;
		std::vector<std::shared_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>>> mMachines;
	};
	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithController(ANPCAIController* controller)
	{
		mController = controller;
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithEventDispatcher(AEventDispatcher* eventDispatcher)
	{
		mEventDispatcher = eventDispatcher;
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithGoal(std::shared_ptr<NAI::Goap::IGoal> goal)
	{
		AgentBuilder::WithGoal(goal);
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
	{
		AgentBuilder::WithPredicate(predicate);
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithGoapPlanner(std::shared_ptr<NAI::Goap::IGoapPlanner> planner)
	{
		AgentBuilder::WithGoapPlanner(planner);
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithSensoryThreshold(const std::string& stimulusClassName,
        std::shared_ptr<NAI::Goap::IThreshold> threshold)
	{
		AgentBuilder::WithSensoryThreshold(stimulusClassName, threshold);
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithPerceptionSystem(
        std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem)
	{
		AgentBuilder::WithPerceptionSystem(sensorySystem);
		return *this;
	}

	template<class TAgent, typename TStateID, class TContext>
    NPCAgentBuilder<TAgent, TStateID, TContext>& NPCAgentBuilder<TAgent, TStateID, TContext>::WithStatesMachine(
        std::shared_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> machine)
	{
		mMachines.push_back(machine);
		return *this;
	}
	
	template<class TAgent, typename TStateID, class TContext>
    std::shared_ptr<NAI::Goap::IAgent> NPCAgentBuilder<TAgent, TStateID, TContext>::Build()
	{
		//TODO the NPCAgent, can be constructed from an IAgent and the extra parameters
		//That way we can use here the Base Build and then create the NPCAgent(agent)
		std::shared_ptr<TAgent> agent;

		if(mSensorySystem)
		{
			agent = std::make_shared<TAgent>(
             mGoapPlanner,
             mGoals,
             mPredicates,
             std::make_shared<NAI::Goap::PerceptionSystem>(mSensorySystem),
             mController);
		}
		else
		{
			agent = std::make_shared<TAgent>(
             mGoapPlanner,
             mGoals,
             mPredicates,
             mController);
		}
		
		for(auto&& threshold : mSensoryThresholds)
		{
			agent->AddSensoryThreshold(threshold.first, threshold.second);
		}

		for(auto&& machine : mMachines)
		{
			auto specificAgent = std::static_pointer_cast<TAgent>(agent);
			specificAgent->AddStatesMachine(machine);
		}
		
		//TODO if is debug
		auto debugAgent = std::make_shared<NPCAgentDebugDecorator<TStateID, TContext>>(agent, mController, mEventDispatcher);

		return debugAgent;
	}
}