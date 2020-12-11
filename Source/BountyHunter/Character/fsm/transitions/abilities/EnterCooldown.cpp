#include <BountyHunter/Character/fsm/transitions/abilities/EnterCooldown.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Abilities/IAbility.h>


namespace TLN
{
	EnterCooldown::EnterCooldown(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterCooldown::OnInit()
	{
	}

	bool EnterCooldown::CanPerformTransition() const
	{
		return GetContext()->GetAbility() && !GetContext()->GetAbility()->IsCasting();
	}
};