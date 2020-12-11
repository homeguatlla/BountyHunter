#include <BountyHunter/Character/fsm/transitions/debug/EnterPreviousNPC.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	EnterPreviousNPC::EnterPreviousNPC(StatePtr origin, StatePtr destination) :
		core::utils::FSM::BaseTransition<CharacterState, CharacterContext>(origin, destination)
	{
	}

	void EnterPreviousNPC::OnInit()
	{
		mInputHandler = GetContext()->GetInputHandler();
	}

	bool EnterPreviousNPC::CanPerformTransition() const
	{
		auto pressed = mInputHandler->IsActionPressed(InputAction::PREVIOUS_NPC);
		mInputHandler->InsertInput(InputAction::PREVIOUS_NPC, false);

		return pressed;
	}
};