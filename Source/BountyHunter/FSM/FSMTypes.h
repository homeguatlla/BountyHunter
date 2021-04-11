#pragma once
#include <string>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"
#include "BountyHunter/Character/fsm/states/CharacterStates.h"

enum class FSMType
{
	CHARACTER_MOVEMENT = 0,
	CHARACTER_ABILITY = 1,
	CHARACTER_SHOT = 2,
	DEBUG = 3,
	
	CHICKEN_MOVEMENT = 10,
	CHICKEN_STATE = 11,
};

template<typename TStateID>
static std::string GetStateName(TStateID stateId)
{
	if(typeid(TStateID) == typeid(TLN::Chicken::ChickenState))
	{
		return TLN::Chicken::ChickenStateMap[static_cast<TLN::Chicken::ChickenState>(stateId)];
	}
	else if(typeid(TStateID) == typeid(TLN::CharacterState))
	{
		return TLN::CharacterStateMap[static_cast<TLN::CharacterState>(stateId)];
	}
	else return "NotFound";
}