#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterWalk.h>

#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		EnterWalk::EnterWalk(StatePtr origin, StatePtr destination) :
         core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterWalk::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool EnterWalk::CanPerformTransition() const
		{
			return mCharacter->GetMovementSpeed() > 0.0f;
		}
	}
}
