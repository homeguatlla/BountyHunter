#pragma once
#include <NAI/include/goap/agent/BaseAgent.h>
#include <NAI/include/goap/IGoapPlanner.h>
#include <stdexcept>
#include <BountyHunter/Agents/AI/IAgentAIController.h>

#include "goap/sensory/PerceptionSystem.h"
#include "CoreMinimal.h"


#include "BountyHunter/FSM/StatesMachineController.h"
#include "goap/sensory/PerceptionSystem.h"
#include "utils/fsm/StatesMachine.h"

class IAgentAIController;

template<typename TStateID, class TContext>
class NPCAgent : public NAI::Goap::BaseAgent
{
public:

	NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
        std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
        std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates,
        IAgentAIController* controller);
	
	NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
		std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
		std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates,
		std::shared_ptr<NAI::Goap::PerceptionSystem> perceptionSystem,
		IAgentAIController* controller);
	~NPCAgent() = default;

	void Update(float elapsedTime) override;
	glm::vec3 GetPosition() const override;
	void MoveTo(float elapsedTime, const glm::vec3& point) override;
	IAgentAIController* GetController() const { return mController; }

	void AddStatesMachine(std::shared_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> machine);

private:
	IAgentAIController* mController;
	StatesMachineController<TStateID, TContext> mStatesMachineController;
};

template<typename TStateID, class TContext>
NPCAgent<TStateID, TContext>::NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
                   std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
                   std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates,
    IAgentAIController* controller) :
    NAI::Goap::BaseAgent(goapPlanner, goals, predicates),
    mController(controller)
{

}

template<typename TStateID, class TContext>
NPCAgent<TStateID, TContext>::NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
                   std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
                   std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates,
                   std::shared_ptr<NAI::Goap::PerceptionSystem> perceptionSystem,
    IAgentAIController* controller) :
    NAI::Goap::BaseAgent(goapPlanner, goals, predicates, perceptionSystem),
    mController(controller)
{

}

template<typename TStateID, class TContext>
void NPCAgent<TStateID, TContext>::Update(float elapsedTime)
{
	BaseAgent::Update(elapsedTime);
	mStatesMachineController.Update(elapsedTime);
}

template<typename TStateID, class TContext>
glm::vec3 NPCAgent<TStateID, TContext>::GetPosition() const
{
	if(mController != nullptr)
	{
		const auto position = mController->GetPosition();

		return glm::vec3(position.X, position.Y, position.Z);
	}
	else
	{
		throw std::logic_error("Controller is not alive! The agent must be removed.");
	}
}

template<typename TStateID, class TContext>
void NPCAgent<TStateID, TContext>::MoveTo(float elapsedTime, const glm::vec3& point)
{
	if (mController != nullptr)
	{
		return mController->MoveTo(elapsedTime, FVector(point.x, point.y, point.z));
	}
	else
	{
		throw std::logic_error("Controller is not alive! The agent must be removed.");
	}
}

template <typename TStateID, class TContext>
void NPCAgent<TStateID, TContext>::AddStatesMachine(std::shared_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> machine)
{
	mStatesMachineController.AddMachine(machine);
}
