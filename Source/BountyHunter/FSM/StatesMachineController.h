#pragma once
#include "utils/fsm/StatesMachine.h"


template<typename TStateID, class TContext>
class StatesMachineController
{
	using StatesMachineType = core::utils::FSM::StatesMachine<TStateID, TContext>;
public:
	StatesMachineController() = default;
	~StatesMachineController() = default;

	void AddMachine(std::shared_ptr<StatesMachineType> machine);
	void Update(float elapsedTime);
	TStateID GetCurrentStateID(unsigned int machineIndex) const;

private:
	std::vector<std::shared_ptr<StatesMachineType>> mMachines;
};

template <typename TStateID, class TContext>
void StatesMachineController<TStateID, TContext>::AddMachine(
	std::shared_ptr<StatesMachineType> machine)
{
	mMachines.push_back(machine);
}

template <typename TStateID, class TContext>
void StatesMachineController<TStateID, TContext>::Update(float elapsedTime)
{
	for(auto&& machine : mMachines)
	{
		machine->Update(elapsedTime);
		UE_LOG(LogTemp, Warning, TEXT("StatesMachineController state:%d"), machine->GetCurrentState()->GetID());
	}
}

template <typename TStateID, class TContext>
TStateID StatesMachineController<TStateID, TContext>::GetCurrentStateID(unsigned machineIndex) const
{
	assert(machineIndex < mMachines.size());

	return mMachines[machineIndex]->GetCurrentState()->GetID();
}
