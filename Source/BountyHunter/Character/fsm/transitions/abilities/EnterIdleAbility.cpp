#include <BountyHunter/Character/fsm/transitions/abilities/EnterIdleAbility.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterIdleAbility::EnterIdleAbility(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterIdleAbility::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	bool EnterIdleAbility::CanPerformTransition() const
	{
		return mCharacter->IsReadyToCast();
	}
};