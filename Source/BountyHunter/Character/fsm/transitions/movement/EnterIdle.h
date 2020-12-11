#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>
#include <BountyHunter/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;

	class EnterIdle : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterIdle(StatePtr origin, StatePtr destination);
		virtual ~EnterIdle() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
	};
};
