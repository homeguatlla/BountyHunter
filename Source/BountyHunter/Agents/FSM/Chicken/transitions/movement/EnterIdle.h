#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class EnterIdle : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterIdle(StatePtr origin, StatePtr destination);
			virtual ~EnterIdle() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	}
};
