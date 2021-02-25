#include "StatesMachineFactory.h"

std::unique_ptr<StatesMachineFactory::CharacterStatesMachine> StatesMachineFactory::CreateCharacter(FSMType type, std::shared_ptr<TLN::CharacterContext> context)
{
	StatesMachineBuilder<TLN::CharacterState, TLN::CharacterContext> builder;

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

std::unique_ptr<StatesMachineFactory::ChickenStatesMachine> StatesMachineFactory::CreateChicken(FSMType type, std::shared_ptr<TLN::Chicken::ChickenContext> context)
{
	StatesMachineBuilder<TLN::Chicken::ChickenState, TLN::Chicken::ChickenContext> builder;

	switch(type)
	{
	case FSMType::CHICKEN_MOVEMENT:
			{
				auto idle = std::make_shared<TLN::Chicken::Idle>();
				auto walk = std::make_shared<TLN::Chicken::Walk>();
				
				return builder.WithState(idle)
                              .WithState(walk)
                              .WithTransition(std::make_unique<TLN::Chicken::EnterWalk>(idle, walk))
                              .WithTransition(std::make_unique<TLN::Chicken::EnterIdle>(walk, idle))
                              .WithInitialState(idle->GetID())
                              .Build(context);
			}
		default:
			checkf(false, TEXT("States Machine type %d not defined"), type);
			return {};
	}	
}