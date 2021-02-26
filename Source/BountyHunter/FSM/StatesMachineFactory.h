#pragma once
#include "FSMTypes.h"
#include "utils/fsm/StatesMachine.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"
#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

#include "BountyHunter/Character/fsm/CharacterContext.h"
#include "BountyHunter/Character/fsm/states/CharacterStates.h"

namespace TLN
{
	class StatesMachineFactory
	{
		using CharacterStatesMachine = core::utils::FSM::StatesMachine<TLN::CharacterState, TLN::CharacterContext>;
		using ChickenStatesMachine = core::utils::FSM::StatesMachine<TLN::Chicken::ChickenState, TLN::Chicken::ChickenContext>;
	public:
		StatesMachineFactory() = default;
		~StatesMachineFactory() = default;

		std::unique_ptr<CharacterStatesMachine> CreateCharacter(FSMType type, std::shared_ptr<TLN::CharacterContext> context);
		std::unique_ptr<ChickenStatesMachine> CreateChicken(FSMType type, std::shared_ptr<TLN::Chicken::ChickenContext> context);
	};
}