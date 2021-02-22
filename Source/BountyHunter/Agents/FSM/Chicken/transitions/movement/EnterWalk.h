#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class EnterWalk : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterWalk(StatePtr origin, StatePtr destination);
			virtual ~EnterWalk() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
	};
	}
};