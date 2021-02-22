#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		
		class ChickenContext;

		class EnterRun : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterRun(StatePtr origin, StatePtr destination);
			virtual ~EnterRun() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;

		};
	};
}
