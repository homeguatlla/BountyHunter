#include "NPCAgent.h"

#include <stdexcept>
#include <BountyHunter/Agents/AI/IAgentAIController.h>

NPCAgent::NPCAgent(std::shared_ptr<NAI::Goap::IGoapPlanner> goapPlanner,
	std::vector<std::shared_ptr<NAI::Goap::IGoal>>& goals,
	std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates,
	IAgentAIController* controller) :
	NAI::Goap::BaseAgent(goapPlanner, goals, predicates),
	mController(controller)
{

}

void NPCAgent::Update(float elapsedTime)
{
	BaseAgent::Update(elapsedTime);
}

glm::vec3 NPCAgent::GetPosition() const
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

void NPCAgent::MoveTo(float elapsedTime, const glm::vec3& point)
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
