#include <BountyHunter/Agents/FSM/Chicken/transitions/state/LeaveEat.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		LeaveEat::LeaveEat(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void LeaveEat::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool LeaveEat::CanPerformTransition() const
		{
			return !mCharacter->IsEating();
		}
	};
}
