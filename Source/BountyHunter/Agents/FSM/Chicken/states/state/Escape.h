#pragma once
#include <NAI/include/utils/fsm/BaseState.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class Escape : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			Escape() = default;
			virtual ~Escape() = default;
			ChickenState GetID() const override { return ChickenState::STATE_ESCAPE; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
		};
	}
};
