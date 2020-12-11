#pragma once
#include <NAI/include/utils/fsm/BaseState.h>
#include <BountyHunter/Character/fsm/states/CharacterStates.h>

namespace TLN
{
	class CharacterContext;
	class ICharacter;

	class Run : public core::utils::FSM::BaseState<CharacterState, CharacterContext>
	{
	public:
		Run() = default;
		virtual ~Run() = default;
		CharacterState GetID() const override { return CharacterState::STATE_RUNNING; }
		void OnInit() override;
		void OnEnter(float deltaTime) override;
		void OnUpdate(float deltaTime) override;

	private:
		ICharacter* mCharacter;
	};
};
