#pragma once
#include <NAI/include/utils/fsm/BaseState.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class Idle : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			Idle() = default;
			virtual ~Idle() = default;
			ChickenState GetID() const override { return ChickenState::STATE_IDLE; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
		};
	}
};
