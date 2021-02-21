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

class StatesMachineFactory
{
public:
	StatesMachineFactory() = default;
	~StatesMachineFactory() = default;

	template <typename TStateID, class TContext>
	std::unique_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> Create(FSMType type, std::shared_ptr<TContext> context);
};

template <typename TStateID, class TContext>
std::unique_ptr<core::utils::FSM::StatesMachine<TStateID, TContext>> StatesMachineFactory::Create(FSMType type, std::shared_ptr<TContext> context)
{
	StatesMachineBuilder<TStateID, TContext> builder;

	switch(type)
	{
		case FSMType::CHARACTER_MOVEMENT:
			{
				auto idle = std::make_shared<TLN::Idle>();
				auto walk = std::make_shared<TLN::Walk>();
				
				return builder.WithState(idle)
                              .WithState(walk)
                              .WithTransition(std::make_unique<TLN::EnterWalk>(idle, walk))
                              .WithTransition(std::make_unique<TLN::EnterIdle>(walk, idle))
                              .WithInitialState(idle->GetID())
                              .Build(context);
			}
		case FSMType::CHARACTER_ABILITY:
			{
				auto idle = std::make_shared<TLN::IdleAbility>();
				auto cast = std::make_shared<TLN::Casting>();
				auto cooldown = std::make_shared<TLN::Cooldown>();

				return builder.WithState(idle)
							  .WithState(cast)
							  .WithState(cooldown)
							  .WithTransition(std::make_unique<TLN::EnterCast>(idle, cast))
							  .WithTransition(std::make_unique<TLN::EnterCooldown>(cast, cooldown))
							  .WithTransition(std::make_unique<TLN::EnterIdleAbility>(cooldown, idle))
							  .WithInitialState(idle->GetID())
							  .Build(context);
			}
		case FSMType::DEBUG:
			{
				auto normal = std::make_shared<TLN::Normal>();
				auto debug = std::make_shared<TLN::Debug>();
				auto nextNPC = std::make_shared<TLN::NextNPC>();
				auto previousNPC = std::make_shared<TLN::PreviousNPC>();

				return builder.WithState(normal)
							  .WithState(debug)
							  .WithState(nextNPC)
							  .WithState(previousNPC)
                              .WithTransition(std::make_unique<TLN::EnterDebug>(normal, debug))
							  .WithTransition(std::make_unique<TLN::EnterNormal>(debug, normal))
							  .WithTransition(std::make_unique<TLN::EnterNextNPC>(debug, nextNPC))
							  .WithTransition(std::make_unique<TLN::EnterPreviousNPC>(debug, previousNPC))
							  .WithTransition(std::make_unique<TLN::LeaveState>(nextNPC, debug))
							  .WithTransition(std::make_unique<TLN::LeaveState>(previousNPC, debug))
							  .WithInitialState(normal->GetID())
							  .Build(context);
			}
		default:
			checkf(false, TEXT("States Machine type %d not defined"), type);
			return {};
	}	
}
