#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

#include "BountyHunter/Agents/FSM/Chicken/states/ChickenStates.h"


namespace TLN
{
	namespace Chicken
	{
		class ChickenContext;

		class Jump : public core::utils::FSM::BaseState<ChickenState, ChickenContext>
		{
		public:
			Jump() = default;
			virtual ~Jump() = default;
			ChickenState GetID() const override { return ChickenState::STATE_JUMPING; }
			void OnInit() override;
			void OnEnter(float deltaTime) override;
		};
	};
}
