#include <BountyHunter/Character/fsm/transitions/shot/EnterCooldownShot.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Abilities/IAbility.h>


namespace TLN
{
	EnterCooldownShot::EnterCooldownShot(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterCooldownShot::OnInit()
	{
	}

	bool EnterCooldownShot::CanPerformTransition() const
	{
		return true;
	}
};