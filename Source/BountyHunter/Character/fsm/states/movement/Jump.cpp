#include <BountyHunter/Character/fsm/states/movement/Jump.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	void Jump::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Jump::OnEnter(float deltaTime)
	{
		//mCharacter->PerformJump(deltaTime);
	}
};
