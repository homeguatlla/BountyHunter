#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class InputHandler;
	class IAbility;

	class EnterCooldown : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterCooldown(StatePtr origin, StatePtr destination);
		virtual ~EnterCooldown() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;
		
	private:
		std::shared_ptr<IAbility> mAbility;
	};
};
