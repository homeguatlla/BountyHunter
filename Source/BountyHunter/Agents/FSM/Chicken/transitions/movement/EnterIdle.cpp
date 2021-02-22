#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterIdle.h>

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
			
		}

		bool EnterIdle::CanPerformTransition() const
		{
			return false;
		}
	};
}