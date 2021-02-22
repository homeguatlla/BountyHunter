#include <BountyHunter/Agents/FSM/Chicken/transitions/movement/EnterJump.h>

namespace TLN
{
	namespace Chicken
	{
		EnterJump::EnterJump(StatePtr origin, StatePtr destination) :
            core::utils::FSM::BaseTransition<ChickenState, ChickenContext>(origin, destination)
		{
		}

		void EnterJump::OnInit()
		{
			
		}

		bool EnterJump::CanPerformTransition() const
		{
			return false;
		}
	}
}