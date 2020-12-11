#include <BountyHunter/Character/fsm/states/movement/OnAir.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	void OnAir::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void OnAir::OnEnter(float deltaTime)
	{
	}
};