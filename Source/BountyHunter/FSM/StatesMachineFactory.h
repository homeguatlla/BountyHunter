#pragma once
#include "FSMTypes.h"
#include "StatesMachineBuilder.h"
#include "utils/fsm/StatesMachine.h"
#include <BountyHunter/Character/fsm/states/movement/Idle.h>
#include <BountyHunter/Character/fsm/states/movement/Walk.h>

#include <BountyHunter/Character/fsm/states/debug/Debug.h>
#include <BountyHunter/Character/fsm/states/debug/Normal.h>
#include <BountyHunter/Character/fsm/states/debug/NextNPC.h>
#include <BountyHunter/Character/fsm/states/debug/PreviousNPC.h>

#include <BountyHunter/Character/fsm/states/abilities/Casting.h>
#include <BountyHunter/Character/fsm/states/abilities/IdleAbility.h>
#include <BountyHunter/Character/fsm/states/abilities/Cooldown.h>

#include <BountyHunter/Character/fsm/transitions/movement/EnterIdle.h>
#include <BountyHunter/Character/fsm/transitions/movement/EnterWalk.h>

#include <BountyHunter/Character/fsm/transitions/abilities/EnterCast.h>
#include <BountyHunter/Character/fsm/transitions/abilities/EnterIdleAbility.h>
#include <BountyHunter/Character/fsm/transitions/abilities/EnterCooldown.h>

#include <BountyHunter/Character/fsm/transitions/debug/EnterNormal.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterDebug.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterNextNPC.h>
#include <BountyHunter/Character/fsm/transitions/debug/EnterPreviousNPC.h>
#include <BountyHunter/Character/fsm/transitions/debug/LeaveState.h>

#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"
#include "BountyHunter/Agents/FSM/Chicken/states/movement/Idle.h"
#include "BountyHunter/Agents/FSM/Chicken/states/movement/Walk.h"
#include "BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterIdle.h"
#include "BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterWalk.h"
#include "BountyHunter/Character/fsm/states/CharacterStates.h"

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
