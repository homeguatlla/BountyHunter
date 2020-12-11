#include <BountyHunter/Character/fsm/states/movement/Walk.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	void Walk::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Walk::OnEnter(float deltaTime)
	{
	}

	void Walk::OnUpdate(float deltaTime)
	{
		mCharacter->PerformMovement();
	}
};

