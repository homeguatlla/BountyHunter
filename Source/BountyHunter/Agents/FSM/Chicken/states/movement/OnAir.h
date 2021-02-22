#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;
		
		class OnAir : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			OnAir() = default;
			virtual ~OnAir() = default;
			ChickenState GetID() const override { return ChickenState::STATE_ON_AIR; }
			void OnInit() override;
			void OnEnter(float deltaTime) override;
		};
	};
}
