#include <BountyHunter/Character/fsm/states/debug/Normal.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/EventDispatcher.h>

namespace TLN
{
	void Normal::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void Normal::OnEnter(float deltaTime)
	{
		mEventDispatcher->OnEnableDebugMode.Broadcast(false);
	}
};