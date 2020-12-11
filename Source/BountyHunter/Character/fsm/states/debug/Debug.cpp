#include <BountyHunter/Character/fsm/states/debug/Debug.h>
#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Debug/DebugData.h>
#include <BountyHunter/EventDispatcher.h>

namespace TLN 
{
	void Debug::OnInit()
	{
		mEventDispatcher = GetContext()->GetEventDispatcher();
	}

	void Debug::OnEnter(float deltaTime)
	{
		auto debugData = GetContext()->GetDebugData();
		mEventDispatcher->OnNextNPC.Broadcast(debugData->GetCurrentNPCController());
		mEventDispatcher->OnEnableDebugMode.Broadcast(true);
	}
};