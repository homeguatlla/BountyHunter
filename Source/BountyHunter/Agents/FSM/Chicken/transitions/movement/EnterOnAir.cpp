#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterOnAir.h>

namespace TLN
{
	namespace Chicken
	{
		EnterOnAir::EnterOnAir(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterOnAir::OnInit()
		{
		}

		bool EnterOnAir::CanPerformTransition() const
		{
			return false;
		}
	}
}