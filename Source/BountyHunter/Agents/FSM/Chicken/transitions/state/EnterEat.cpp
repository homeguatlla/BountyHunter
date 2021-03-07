#include <BountyHunter/Agents/FSM/Chicken/transitions/state/EnterEat.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		EnterEat::EnterEat(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterEat::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool EnterEat::CanPerformTransition() const
		{
			return mCharacter->IsEating();
		}
	};
}
