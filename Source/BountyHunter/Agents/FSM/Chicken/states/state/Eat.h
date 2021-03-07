#pragma once
#include <NAI/include/utils/fsm/BaseState.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class Eat : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			Eat() = default;
			virtual ~Eat() = default;
			ChickenState GetID() const override { return ChickenState::STATE_EAT; }

			void OnInit() override;
			void OnEnter(float deltaTime) override;
		};
	}
};
