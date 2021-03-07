#pragma once
#include <NAI/include/utils/fsm/BaseTransition.h>
#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN {
	class INPCCharacter;
}

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class EnterExplore : public core::utils::FSM::BaseTransition<ChickenState, ChickenContext>
		{
		public:
			EnterExplore(StatePtr origin, StatePtr destination);
			virtual ~EnterExplore() = default;

			void OnInit() override;
			bool CanPerformTransition() const override;

		private:
			INPCCharacter* mCharacter;	
		};
	}
};
