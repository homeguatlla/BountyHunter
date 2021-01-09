#include "NPCAgentDecorator.h"


NPCAgentDecorator::NPCAgentDecorator(std::shared_ptr<NAI::Goap::IAgent> agent) : 
mAgent{ agent },
mIsEnabled {true}
{
}

void NPCAgentDecorator::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);
}

glm::vec3 NPCAgentDecorator::GetPosition() const
{
	return mAgent->GetPosition();
}

void NPCAgentDecorator::MoveTo(float elapsedTime, const glm::vec3& point)
{
	mAgent->MoveTo(elapsedTime, point);
}

void NPCAgentDecorator::StartUp()
{
	mAgent->StartUp();
}

NAI::Goap::AgentState NPCAgentDecorator::GetCurrentState() const
{
	return mAgent->GetCurrentState();
}

bool NPCAgentDecorator::HasPredicate(int predicateID) const
{
	return mAgent->HasPredicate(predicateID);
}

std::string NPCAgentDecorator::WhereIam() const
{
	return mAgent->WhereIam();
}

void NPCAgentDecorator::OnNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	mAgent->OnNewPredicate(predicate);
}

const std::vector<std::shared_ptr<NAI::Goap::IGoal>>& NPCAgentDecorator::GetGoals() const
{
	return mAgent->GetGoals();
}

const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& NPCAgentDecorator::GetPredicates() const
{
	return mAgent->GetPredicates();
}

bool NPCAgentDecorator::IsStimulusAccepted(std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	return mAgent->IsStimulusAccepted(stimulus);
}

const std::vector<std::shared_ptr<NAI::Goap::IPredicate>> NPCAgentDecorator::TransformStimulusIntoPredicates(
	std::shared_ptr<NAI::Goap::IStimulus> stimulus) const
{
	return mAgent->TransformStimulusIntoPredicates(stimulus);
}

void NPCAgentDecorator::AddSensoryThreshold(const std::string& stimulusClassName,
	std::shared_ptr<NAI::Goap::IThreshold> threshold)
{
	mAgent->AddSensoryThreshold(stimulusClassName, threshold);
}

std::map<std::string, std::shared_ptr<NAI::Goap::IThreshold>> NPCAgentDecorator::GetSensoryThresholds() const
{
	return mAgent->GetSensoryThresholds();
}
