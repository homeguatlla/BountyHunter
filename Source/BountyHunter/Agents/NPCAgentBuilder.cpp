#include "NPCAgentBuilder.h"

NPCAgentBuilder& NPCAgentBuilder::WithController(ANPCAIController* controller)
{
	mController = controller;
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithEventDispatcher(AEventDispatcher* eventDispatcher)
{
	mEventDispatcher = eventDispatcher;
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithGoal(std::shared_ptr<NAI::Goap::IGoal> goal)
{
	AgentBuilder::WithGoal(goal);
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	AgentBuilder::WithPredicate(predicate);
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithGoapPlanner(std::shared_ptr<NAI::Goap::IGoapPlanner> planner)
{
	AgentBuilder::WithGoapPlanner(planner);
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithSensoryThreshold(const std::string& stimulusClassName,
	std::shared_ptr<NAI::Goap::IThreshold> threshold)
{
	AgentBuilder::WithSensoryThreshold(stimulusClassName, threshold);
	return *this;
}

NPCAgentBuilder& NPCAgentBuilder::WithPerceptionSystem(
	std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem)
{
	AgentBuilder::WithPerceptionSystem(sensorySystem);
	return *this;
}
