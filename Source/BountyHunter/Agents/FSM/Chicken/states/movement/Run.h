#pragma once
#include <NAI/include/utils/fsm/BaseState.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class Run : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			Run() = default;
			virtual ~Run() = default;
			ChickenState GetID() const override { return ChickenState::STATE_RUNNING; }
			void OnInit() override;
			void OnEnter(float deltaTime) override;
			void OnUpdate(float deltaTime) override;

		};
	}
};
