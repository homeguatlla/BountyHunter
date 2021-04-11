#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class IAbility;

	class CooldownShot : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		CooldownShot() = default;
		virtual ~CooldownShot() = default;
		CharacterState GetID() const override { return CharacterState::STATE_COOLDOWN_SHOT; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;
		void OnExit(float deltaTime) override;
	};
};
