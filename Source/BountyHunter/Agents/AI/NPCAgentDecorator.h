#pragma once
#include <NAI/include/goap/agent/IAgent.h>

class NPCAgentDecorator : public NAI::Goap::IAgent
{
public:
	NPCAgentDecorator(std::shared_ptr<NAI::Goap::IAgent> agent);
	~NPCAgentDecorator() = default;

	virtual void Update(float elapsedTime) override;
	glm::vec3 GetPosition() const override;
	void MoveTo(float elapsedTime, const glm::vec3& point) override;
	void StartUp() override;
	NAI::Goap::AgentState GetCurrentState() const override;
	bool HasPredicate(int predicateID) const override;
	std::string WhereIam() const override;
	void OnNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate) override;
	void OnUpdatePredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate) override;
	const std::vector<std::shared_ptr<NAI::Goap::IGoal>>& GetGoals() const override;
	const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& GetPredicates() const override;
	const std::vector<std::shared_ptr<NAI::Goap::IPredicate>> TransformStimulusIntoPredicates(const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const override;
	void AddSensoryThreshold(const std::string& stimulusClassName,
		std::shared_ptr<NAI::Goap::IThreshold> threshold) override;
	std::map<std::string, std::shared_ptr<NAI::Goap::IThreshold>> GetSensoryThresholds() const override;
	void RemovePredicate(int id) override;
	void AddNewGoal(std::shared_ptr<NAI::Goap::IGoal> goal) override;

	bool IsEnabled() const { return mIsEnabled; }
	void SetEnabled(bool enabled) { mIsEnabled = enabled; }

protected:
	std::shared_ptr<NAI::Goap::IAgent> mAgent;
	bool mIsEnabled;
};