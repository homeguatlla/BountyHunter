#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class ICharacter;
	class CharacterContext;
	class IAbility;

	class Fire : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Fire() = default;
		virtual ~Fire() = default;
		CharacterState GetID() const override { return CharacterState::STATE_FIRE; }

		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;
		void OnExit(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};
