#include <BountyHunter/Agents/FSM/Chicken/transitions/state/EnterEscape.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		EnterEscape::EnterEscape(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterEscape::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool EnterEscape::CanPerformTransition() const
		{
			return mCharacter->IsEscaping();
		}
	};
}
