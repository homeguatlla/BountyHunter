#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext;

	class IdleShot : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		IdleShot() = default;
		virtual ~IdleShot() = default;
		CharacterState GetID() const override { return CharacterState::STATE_IDLE_SHOT; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};
