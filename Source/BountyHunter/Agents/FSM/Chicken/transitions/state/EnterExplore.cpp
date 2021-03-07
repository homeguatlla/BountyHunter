#include <BountyHunter/Agents/FSM/Chicken/transitions/state/EnterExplore.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		EnterExplore::EnterExplore(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterExplore::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool EnterExplore::CanPerformTransition() const
		{
			return mCharacter->IsExploring();
		}
	};
}
