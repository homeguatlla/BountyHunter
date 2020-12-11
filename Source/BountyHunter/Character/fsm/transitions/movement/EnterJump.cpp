#include <BountyHunter/Character/fsm/transitions/movement/EnterJump.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterJump::EnterJump(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterJump::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterJump::CanPerformTransition() const
	{
		return false;
		//return mPlayer->IsActionActive(PlayerAction::Jump);
	}
}