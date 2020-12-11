#include <BountyHunter/Character/fsm/states/abilities/Casting.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Abilities/IAbility.h>

namespace TLN
{
	void Casting::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Casting::OnEnter(float deltaTime)
	{
		mCharacter->PlayCastingAnimation();
		mAbility = mCharacter->Cast();
		GetContext()->SetAbility(mAbility);
	}

	void Casting::OnUpdate(float deltaTime)
	{
		mAbility->Update(deltaTime);
	}

	void Casting::OnExit(float deltaTime)
	{
		mCharacter->StopCastingAnimation();
	}
};