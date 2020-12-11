#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>
#include <BountyHunter/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterWalk : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterWalk(StatePtr origin, StatePtr destination);
		virtual ~EnterWalk() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};