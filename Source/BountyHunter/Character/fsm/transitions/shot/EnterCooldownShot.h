#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class InputHandler;
	class IAbility;

	class EnterCooldownShot : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterCooldownShot(StatePtr origin, StatePtr destination);
		virtual ~EnterCooldownShot() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;
		
	private:
		std::shared_ptr<IAbility> mAbility;
	};
};
