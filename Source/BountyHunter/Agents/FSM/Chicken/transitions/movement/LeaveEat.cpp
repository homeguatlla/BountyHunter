#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/LeaveEat.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"
#include "BountyHunter/utils/UtilsLibrary.h"

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
