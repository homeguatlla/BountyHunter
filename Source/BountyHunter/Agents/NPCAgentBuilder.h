#pragma once
#include <vector>
#include <memory>
#include <BountyHunter/Agents/AI/NPCAgentDebugDecorator.h>

#include "goap/agent/AgentBuilder.h"
#include "goap/sensory/PerceptionSystem.h"

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

class NPCAgentDecorator;

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
	
	template<class TAgent>
	std::shared_ptr<NAI::Goap::IAgent> Build()
	{
		//TODO the NPCAgent, can be constructed from an IAgent and the extra parameters
		//That way we can use here the Base Build and then create the NPCAgent(agent)
		std::shared_ptr<NAI::Goap::IAgent> agent;

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
		
		//TODO if is debug
		auto debugAgent = std::make_shared<NPCAgentDebugDecorator>(agent, mController, mEventDispatcher);

		return debugAgent;
	}
	
private:
	ANPCAIController* mController;
	AEventDispatcher* mEventDispatcher;
};
