#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterRun.h>

namespace TLN
{
	namespace Chicken
	{
		EnterRun::EnterRun(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterRun::OnInit()
		{
		}

		bool EnterRun::CanPerformTransition() const
		{
			return false;
		}
	}
}