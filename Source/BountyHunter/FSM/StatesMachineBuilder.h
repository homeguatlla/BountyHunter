#pragma once
#include "utils/fsm/IState.h"
#include "utils/fsm/StatesMachine.h"

template<typename TStateID, class TContext>
class StatesMachineBuilder
{
public:
	StatesMachineBuilder() = default;
	~StatesMachineBuilder() = default;


	StatesMachineBuilder<TStateID, TContext>& WithState(std::shared_ptr<core::utils::FSM::IState<TStateID, TContext>> state);
	StatesMachineBuilder<TStateID, TContext>& WithTransition(std::unique_ptr<core::utils::FSM::ITransition<TStateID, TContext>> transition);
	StatesMachineBuilder<TStateID, TContext>& WithInitialState(TStateID state);
	
	std::unique_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> Build(std::shared_ptr<TContext> context);

private:
	std::vector<std::shared_ptr<core::utils::FSM::IState<TStateID, TContext>>> mStates;
	std::vector<std::unique_ptr<core::utils::FSM::ITransition<TStateID, TContext>>> mTransitions;
	TStateID mInitialState;
};

template <typename TStateID, class TContext>
StatesMachineBuilder<TStateID, TContext>& StatesMachineBuilder<TStateID, TContext>::WithState(
	std::shared_ptr<core::utils::FSM::IState<TStateID, TContext>> state)
{
	mStates.push_back(state);
	return *this;
}

template <typename TStateID, class TContext>
StatesMachineBuilder<TStateID, TContext>& StatesMachineBuilder<TStateID, TContext>::WithTransition(
	std::unique_ptr<core::utils::FSM::ITransition<TStateID, TContext>> transition)
{
	mTransitions.push_back(std::move(transition));
	return *this;
}

template <typename TStateID, class TContext>
StatesMachineBuilder<TStateID, TContext>& StatesMachineBuilder<TStateID, TContext>::WithInitialState(
	TStateID state)
{
	mInitialState = state;
	return *this;
}

template <typename TStateID, class TContext>
std::unique_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> StatesMachineBuilder<TStateID, TContext>::Build(std::shared_ptr<TContext> context)
{
	auto statesMachine = std::make_unique<core::utils::FSM::StatesMachine<TStateID, TContext>>(context);

	for(auto&& state : mStates)
	{
		statesMachine->AddState(state);
	}

	for(auto&& transition : mTransitions)
	{
		statesMachine->AddTransition(std::move(transition));
	}
	statesMachine->SetInitialState(mInitialState);
	
	return std::move(statesMachine);
}
