#include <BountyHunter/Character/fsm/CharacterContext.h>
#include <BountyHunter/Character/ICharacter.h>
#include <BountyHunter/BountyHunterGameMode.h>
#include <BountyHunter/Debug/DebugData.h>
#include <BountyHunter/utils/UtilsLibrary.h>

namespace TLN
{
	CharacterContext::CharacterContext(
		UWorld* world, 
		TLN::ICharacter* character, 
		std::shared_ptr<InputHandler> input,
		std::shared_ptr<DebugData> debugData) :
		mWorld {world},
		mCharacter {character},
		mInputHandler {input},
		mDebugData { debugData }

	{
		auto gameMode = world->GetAuthGameMode<ABountyHunterGameMode>();
		if (gameMode->IsValidLowLevel())
		{
			mEventDispatcher = gameMode->GetEventDispatcher();
		}

		InitializeDebugData();
	}

	ICharacter* CharacterContext::GetCharacter()
	{
		return mCharacter;
	}

	std::shared_ptr<InputHandler> CharacterContext::GetInputHandler()
	{
		return mInputHandler;
	}

	void CharacterContext::SetAbility(std::shared_ptr<IAbility> ability)
	{
		mAbility = ability;
	}

	std::vector<ANPCAIController*> CharacterContext::GetAllNPCAgentControllers() const
	{
		auto npcActors = utils::UtilsLibrary::GetAllActorsOfClass<ANPCAIController>(
			mWorld,
			ANPCAIController::StaticClass());

		std::vector<ANPCAIController*> controllers;

		for (auto&& actor : npcActors)
		{
			auto controller = Cast<ANPCAIController>(actor);
			controllers.push_back(controller);
		}
		return controllers;
	}

	AEventDispatcher* CharacterContext::GetEventDispatcher()
	{
		return mEventDispatcher;
	}

	void CharacterContext::InitializeDebugData()
	{
		auto npcControllers = GetAllNPCAgentControllers();
		if(!npcControllers.empty())
		{
			mDebugData->SetCurrentNPCController(npcControllers[0]);
		}
	}
}