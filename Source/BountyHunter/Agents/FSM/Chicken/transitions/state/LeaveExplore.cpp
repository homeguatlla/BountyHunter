#include <BountyHunter/Agents/FSM/Chicken/transitions/state/LeaveExplore.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		LeaveExplore::LeaveExplore(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void LeaveExplore::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool LeaveExplore::CanPerformTransition() const
		{
			return !mCharacter->IsExploring();
		}
	};
}
