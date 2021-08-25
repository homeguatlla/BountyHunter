#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>
#include <BountyHunter/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterIdleShot : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterIdleShot(StatePtr origin, StatePtr destination);
		virtual ~EnterIdleShot() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};