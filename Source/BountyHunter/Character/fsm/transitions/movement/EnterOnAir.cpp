#include <BountyHunter/Character/fsm/transitions/movement/EnterOnAir.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterOnAir::EnterOnAir(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterOnAir::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterOnAir::CanPerformTransition() const
	{
		return false;
	}
}