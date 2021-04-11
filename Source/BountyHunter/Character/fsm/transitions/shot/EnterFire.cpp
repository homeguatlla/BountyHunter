#include <BountyHunter/Character/fsm/transitions/shot/EnterFire.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterFire::EnterFire(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterFire::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterFire::CanPerformTransition() const
	{
		return mInputHandler->IsActionPressed(InputAction::FIRE) && mCharacter->CanFire();
	}
};