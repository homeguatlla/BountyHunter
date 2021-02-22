#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class EnterOnAir : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterOnAir(StatePtr origin, StatePtr destination);
			virtual ~EnterOnAir() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;
		};
	};
}
