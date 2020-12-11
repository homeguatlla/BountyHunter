#include <BountyHunter/Character/fsm/states/abilities/Cooldown.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Abilities/IAbility.h>

namespace TLN
{
	void Cooldown::OnInit()
	{
	}

	void Cooldown::OnEnter(float deltaTime)
	{
		mAbility = GetContext()->GetAbility();
	}

	void Cooldown::OnUpdate(float deltaTime)
	{
		mAbility->Update(deltaTime);
	}

	void Cooldown::OnExit(float deltaTime)
	{
		GetContext()->SetAbility(nullptr);
	}
};