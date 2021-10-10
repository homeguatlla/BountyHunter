#pragma once
#include "BountyHunter/Agents/AI/Actions/FindEscapePlaceAction.h"
#include "BountyHunter/Agents/Components/IEscapeComponent.h"
#include "goap/BaseGoal.h"
#include "goap/goals/GoToGoal.h"

namespace NAI {
	namespace Navigation {
		class INavigationPlanner;
	}
}

class EscapeGoal : public NAI::Goap::BaseGoal, public NAI::Goap::IGoToGoal
{
public:
	EscapeGoal(
		IIEscapeComponent* component,
		const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner,
		float precision = 10.0f);

	virtual void OnNavigationPath(const std::string& placeName,
			const std::shared_ptr<NAI::Navigation::INavigationPath>& path) override;
	virtual glm::vec3 GetDestination(const std::shared_ptr<NAI::Goap::IPredicate> predicate) const override;
	void OnEscapeDirection(const glm::vec3& direction);

protected:
	virtual void DoCreate(const std::shared_ptr<NAI::Goap::IAgent>& agent) override;
	virtual void DoAccomplished(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual void DoCancel(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual void DoReset(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates) override;
	virtual std::shared_ptr<NAI::Goap::IPredicate> DoTransformStimulusIntoPredicates(
		const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;

private:
	std::shared_ptr<FindEscapePlaceAction> CreateFindEscapePlaceAction();
	std::shared_ptr<NAI::Goap::FindPathToAction> CreateFindPathToAction(
		const std::weak_ptr<NAI::Goap::IAgent>& agent,
		const std::shared_ptr<NAI::Navigation::INavigationPlanner>& navigationPlanner);
	std::shared_ptr<NAI::Goap::FollowPathAction> CreateFollowPathAction(
		const std::weak_ptr<NAI::Goap::IAgent>& agent,
		const std::shared_ptr<NAI::Navigation::INavigationPath>& navigationPath) const;

	IIEscapeComponent* mEscapeComponent;
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
	glm::vec3 mEscapeDirection;
	float mPrecision;
};
