#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>
#include <BountyHunter/Character/ICharacter.h>

namespace TLN
{
	class CharacterContext;
	class InputHandler;

	class EnterFire : public core::utils::FSM::BaseTransition<CharacterState, CharacterContext>
	{
	public:
		EnterFire(StatePtr origin, StatePtr destination);
		virtual ~EnterFire() = default;

		void OnInit() override;
		bool CanPerformTransition() const override;

	private:
		ICharacter* mCharacter;
		std::shared_ptr<InputHandler> mInputHandler;
	};
};
