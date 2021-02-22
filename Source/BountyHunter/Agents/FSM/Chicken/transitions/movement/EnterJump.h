#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class EnterJump : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterJump(StatePtr origin, StatePtr destination);
			virtual ~EnterJump() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;

		};
	};
}
