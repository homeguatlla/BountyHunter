#include <BountyHunter/Character/fsm/states/movement/Run.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>

namespace TLN
{
	void Run::OnInit()
	{
		mCharacter = GetContext()->GetCharacter();
	}

	void Run::OnEnter(float deltaTime)
	{
		//mPlayer->PlayAnimation("animation_0");
		//mPlayer->EnableRun(true);
	}

	void Run::OnUpdate(float deltaTime)
	{
		//mPlayer->PerformMovement(deltaTime);
	}
};
