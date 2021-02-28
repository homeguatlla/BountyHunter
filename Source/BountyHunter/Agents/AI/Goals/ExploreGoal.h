#pragma once
#include <NAI/include/goap/BaseGoal.h>

#include "goap/agent/IAgent.h"
#include "goap/goals/GoToGoal.h"

class IIExploreComponent;

class ExploreGoal : public NAI::Goap::GoToGoal
{
public:
	ExploreGoal(
		IIExploreComponent* exploreComponent,
		const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
		float precision = 0.01f);
	
	virtual ~ExploreGoal() = default;
	unsigned GetCost() const override { return 100; }
	void OnExploreLocation(const glm::vec3& location);

protected:
	void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	void AddActions();
	std::shared_ptr<NAI::Goap::IAction> CreateExploreAction();

private:

	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	IIExploreComponent* mExploreComponent;
	std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
};
