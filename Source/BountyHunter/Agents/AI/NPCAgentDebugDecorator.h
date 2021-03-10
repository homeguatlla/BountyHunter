#pragma once
#include <BountyHunter/Agents/AI/NPCAgentDecorator.h>
#include <BountyHunter/Agents/AI/NPCAIController.h>
#include <BountyHunter/EventDispatcher.h>
#include <BountyHunter/utils/UtilsLibrary.h>

#include "CoreMinimal.h"
#include <string>
#include <vector>
#include <algorithm>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"


enum class PredicateStateType
{
	NORMAL = 0,
	NEW = 1,
	REMOVING = 2
};

struct Predicate
{
	Predicate(const std::string& text, PredicateStateType type, float timer = 0.0f) :
		text {text}, type {type}, timer {timer} {}
	
	std::string text;
	PredicateStateType type;
	float timer;
};

template<typename TStateID, class TContext>
class NPCAgentDebugDecorator : public NPCAgentDecorator<TStateID, TContext>
{
public:

	NPCAgentDebugDecorator(std::shared_ptr<NPCAgent<TStateID, TContext>> agent, ANPCAIController* controller, AEventDispatcher* eventDispatcher);
	~NPCAgentDebugDecorator() = default;

	void Update(float elapsedTime) override;

private:
		void UpdateAndRemovePredicatesList(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates);
		void AddNewPredicates(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates);
		void SendPredicatesData() const;
		void SendStateData() const;
		void UpdatePredicateStates(float elapsedTime);
	
private:
		AEventDispatcher* mEventDispatcher;
		ANPCAIController* mController;
		std::vector<Predicate> mPredicates;
};

const float NEW_PREDICATE_TIME = 5.0f;
const float	REMOVING_PREDICATE_TIME = 3.0f;

template<typename TStateID, class TContext>
NPCAgentDebugDecorator<TStateID, TContext>::NPCAgentDebugDecorator(
std::shared_ptr<NPCAgent<TStateID, TContext>> agent, 
ANPCAIController* controller,
AEventDispatcher* eventDispatcher) :
NPCAgentDecorator(agent),
mEventDispatcher(eventDispatcher),
mController(controller)

{
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::Update(float elapsedTime)
{
	mAgent->Update(elapsedTime);
	
	if(IsEnabled())
	{
		auto predicates = mAgent->GetPredicates();
		UpdateAndRemovePredicatesList(predicates);
		AddNewPredicates(predicates);
		UpdatePredicateStates(elapsedTime);
		//TODO improvement: we can only send data when data has changed. The problem is that
		//we need to know a npc change to mark data as dirty. We cannot receive the nextNPC, previousNPC events
		//due this is not a unreal class. 
		SendPredicatesData();
		SendStateData();
	}
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::UpdateAndRemovePredicatesList(std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	for(auto&& predicate : mPredicates)
	{
		auto it = std::find_if(
			predicates.begin(),
			predicates.end(), 
			[predicate](const std::shared_ptr<NAI::Goap::IPredicate> element)
			{
				return predicate.text.compare(element->GetFullText()) == 0;
			});
		
		const bool found = it != predicates.end();
		if(found)
		{
			if(predicate.type == PredicateStateType::REMOVING)
			{
				predicate.type = PredicateStateType::NORMAL;
				predicate.timer = 0.0f;
			}
			predicates.erase(it);
		}
		else if(predicate.type != PredicateStateType::REMOVING)
		{
			predicate.type = PredicateStateType::REMOVING;
			predicate.timer = REMOVING_PREDICATE_TIME;
		}
	}
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::AddNewPredicates(const std::vector<std::shared_ptr<NAI::Goap::IPredicate>>& predicates)
{
	for(const auto predicate : predicates)
	{
		mPredicates.push_back(Predicate{predicate->GetFullText(), PredicateStateType::NEW, NEW_PREDICATE_TIME });
	}
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::SendPredicatesData() const
{
	mEventDispatcher->OnLogClear.Broadcast(mController);
	
	for (auto&& predicate : mPredicates)
	{
		mEventDispatcher->OnLogPredicate.Broadcast(
			mController,
			static_cast<int>(predicate.type),
			utils::UtilsLibrary::ConvertToFString(predicate.text));
	}
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::SendStateData() const
{
	TArray<FString> statesNames;
	mAgent->PerformActionOnEachCurrentState([&statesNames](std::shared_ptr<core::utils::FSM::IState<TStateID, TContext>> state)
	{
		const auto stateName = GetStateName<TStateID>(state->GetID());
		statesNames.Add(utils::UtilsLibrary::ConvertToFString(stateName));
	});
	
	mEventDispatcher->OnLogState.Broadcast(mController, statesNames);
}

template<typename TStateID, class TContext>
void NPCAgentDebugDecorator<TStateID, TContext>::UpdatePredicateStates(float elapsedTime)
{
	for (auto it = mPredicates.begin(); it < mPredicates.end();)
	{
		switch(it->type)
		{
			case PredicateStateType::NEW:
				it->timer -= elapsedTime;
				if(it->timer <= 0)
				{
					it->timer = 0.0f;
					it->type = PredicateStateType::NORMAL;
				}
				++it;
			break;
			case PredicateStateType::REMOVING:
				it->timer -= elapsedTime;
				if (it->timer <= 0)
				{
					it = mPredicates.erase(it);
				}
				else
				{
					++it;
				}
			break;
			default:
				++it;
			break;
		}
	}
}