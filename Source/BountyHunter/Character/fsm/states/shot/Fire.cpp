#include <BountyHunter/Character/fsm/states/shot/Fire.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

#include "BountyHunter/Character/ICharacter.h"

namespace TLN
{
	void Fire::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Fire::OnEnter(float deltaTime)
	{
		mCharacter->Fire();
	}

	void Fire::OnUpdate(float deltaTime)
	{
		
	}

	void Fire::OnExit(float deltaTime)
	{
		
	}
};