#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterEat.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"
#include "BountyHunter/utils/UtilsLibrary.h"

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
