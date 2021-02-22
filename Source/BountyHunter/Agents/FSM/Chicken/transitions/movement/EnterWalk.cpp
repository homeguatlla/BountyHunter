#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterWalk.h>

namespace TLN
{
	namespace Chicken
	{
		EnterWalk::EnterWalk(StatePtr origin, StatePtr destination) :
         core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterWalk::OnInit()
		{
		}

		bool EnterWalk::CanPerformTransition() const
		{
			return false;
		}
	}
}