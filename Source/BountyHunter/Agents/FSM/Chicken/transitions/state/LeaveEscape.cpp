#include <BountyHunter/Agents/FSM/Chicken/transitions/state/LeaveEscape.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		LeaveEscape::LeaveEscape(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void LeaveEscape::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool LeaveEscape::CanPerformTransition() const
		{
			return !mCharacter->IsEscaping();
		}
	};
}
