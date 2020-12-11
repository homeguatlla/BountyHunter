#include <BountyHunter/Character/fsm/transitions/movement/EnterIdle.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterIdle::EnterIdle(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterIdle::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterIdle::CanPerformTransition() const
	{
		return mCharacter->IsIdle();
	}
};