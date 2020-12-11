#include <BountyHunter/Character/fsm/transitions/movement/EnterRun.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterRun::EnterRun(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterRun::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterRun::CanPerformTransition() const
	{
		return false;
	}
}