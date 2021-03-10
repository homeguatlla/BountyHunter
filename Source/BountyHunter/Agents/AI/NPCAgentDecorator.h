#pragma once
#include <NAI/include/goap/agent/IAgent.h>
#include <BountyHunter/Agents/AI/NPCAgent.h>

template<typename TStateID, class TContext>
class NPCAgentDecorator : public NAI::Goap::IAgent
{
public:
	NPCAgentDecorator(std::shared_ptr<NPCAgent<TStateID, TContext>> agent);
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
	std::shared_ptr<NPCAgent<TStateID, TContext>> mAgent;
	bool mIsEnabled;
};
template<typename TStateID, class TContext>
NPCAgentDecorator<TStateID, TContext>::NPCAgentDecorator(std::shared_ptr<NPCAgent<TStateID, TContext>> agent) : 
mAgent{ agent },
mIsEnabled {true}
{
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);
}

template<typename TStateID, class TContext>
glm::vec3 NPCAgentDecorator<TStateID, TContext>::GetPosition() const
{
	return mAgent->GetPosition();
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::MoveTo(float elapsedTime, const glm::vec3& point)
{
	mAgent->MoveTo(elapsedTime, point);
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::StartUp()
{
	mAgent->StartUp();
}

template<typename TStateID, class TContext>
NAI::Goap::AgentState NPCAgentDecorator<TStateID, TContext>::GetCurrentState() const
{
	return mAgent->GetCurrentState();
}

template<typename TStateID, class TContext>
bool NPCAgentDecorator<TStateID, TContext>::HasPredicate(int predicateID) const
{
	return mAgent->HasPredicate(predicateID);
}

template<typename TStateID, class TContext>
std::string NPCAgentDecorator<TStateID, TContext>::WhereIam() const
{
	return mAgent->WhereIam();
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::OnNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	mAgent->OnNewPredicate(predicate);
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::OnUpdatePredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	mAgent->OnUpdatePredicate(predicate);
}

template<typename TStateID, class TContext>
const std::vector<std::shared_ptr<NAI::Goap::IGoal>>& NPCAgentDecorator<TStateID, TContext>::GetGoals() const
{
	return mAgent->GetGoals();
}

template<typename TStateID, class TContext>
const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& NPCAgentDecorator<TStateID, TContext>::GetPredicates() const
{
	return mAgent->GetPredicates();
}

template<typename TStateID, class TContext>
const std::vector<std::shared_ptr<NAI::Goap::IPredicate>> NPCAgentDecorator<TStateID, TContext>::TransformStimulusIntoPredicates(
	const NAI::Goap::ShortTermMemory<NAI::Goap::IStimulus>& memory) const
{
	return mAgent->TransformStimulusIntoPredicates(memory);
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::AddSensoryThreshold(const std::string& stimulusClassName,
	std::shared_ptr<NAI::Goap::IThreshold> threshold)
{
	mAgent->AddSensoryThreshold(stimulusClassName, threshold);
}

template<typename TStateID, class TContext>
std::map<std::string, std::shared_ptr<NAI::Goap::IThreshold>> NPCAgentDecorator<TStateID, TContext>::GetSensoryThresholds() const
{
	return mAgent->GetSensoryThresholds();
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::RemovePredicate(int id)
{
	mAgent->RemovePredicate(id);
}

template<typename TStateID, class TContext>
void NPCAgentDecorator<TStateID, TContext>::AddNewGoal(std::shared_ptr<NAI::Goap::IGoal> goal)
{
	mAgent->AddNewGoal(goal);
}