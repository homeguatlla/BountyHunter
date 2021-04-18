#pragma once
#include <NAI/include/goap/BaseGoal.h>

#include "goap/agent/IAgent.h"
#include "goap/goals/GoToGoal.h"

class IIHomeComponent;
class WaitAction;

class GoToHomeGoal : public NAI::Goap::BaseGoal, public NAI::Goap::IGoToGoal
{
public:
	GoToHomeGoal(
		IIHomeComponent* homeComponent,
		const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
		float precision = 10.0f);
	
	virtual ~GoToHomeGoal() = default;
	unsigned GetCost() const override { return 0; } //TODO maybe 
	unsigned GetCost(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& inputPredicates) const override { return 100; }	
	void OnNavigationPath(const std::string& placeName, const std::shared_ptr<NAI::Navigation::INavigationPath>& path) override;
	glm::vec3 GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const override;

protected:
	void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	void DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	
	void AddActions();
	void RemovePredicates(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) const;
	
	std::shared_ptr<NAI::Goap::FollowPathAction> CreateFollowPathAction(
		const std::weak_ptr<NAI::Goap::IAgent>& agent,
		const std::shared_ptr<NAI::Navigation::INavigationPath>& navigationPath) const;
	std::shared_ptr<NAI::Goap::FindPathToAction> CreateFindPathToAction(
		const std::weak_ptr<NAI::Goap::IAgent>& agent,
		const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner);
			
private:

	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	IIHomeComponent* mHomeComponent;
	std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
	float mPrecision;
};
