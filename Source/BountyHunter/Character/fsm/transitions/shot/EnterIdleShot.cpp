#include <BountyHunter/Character/fsm/transitions/shot/EnterIdleShot.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterIdleShot::EnterIdleShot(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterIdleShot::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterIdleShot::CanPerformTransition() const
	{
		return mCharacter->IsReadyToFire();
	}
};