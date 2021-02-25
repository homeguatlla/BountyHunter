#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterIdle.h>


#include "BountyHunter/Agents/INPCCharacter.h"
#include "BountyHunter/Agents/FSM/Chicken/ChickenContext.h"
#include "BountyHunter/utils/UtilsLibrary.h"

namespace TLN
{
	namespace Chicken
	{
		EnterIdle::EnterIdle(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterIdle::OnInit()
		{
			mCharacter = GetContext()->GetCharacter();
		}

		bool EnterIdle::CanPerformTransition() const
		{
			//TODO crear una comprobacion de igualdad para floats en la libreria de mates.
			return fabs(mCharacter->GetMovementSpeed() - 0.0f) < 0.01f;
		}
	};
}
