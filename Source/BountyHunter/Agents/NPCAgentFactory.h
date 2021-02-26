#pragma once
#include <memory>

#include "NPCTypes.h"

namespace TLN {
	class INPCCharacter;
}

class ANPCAIController;
class AEventDispatcher;

namespace NAI {
	namespace Goap {
		class IStimulus;
		class IAgent;
		template<class T>
		class SensorySystem;
	}
	namespace Navigation {
		class INavigationPlanner;
	}
}

namespace TLN
{
	class NPCAgentFactory
	{
	public:
		NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner);
		virtual ~NPCAgentFactory() = default;

		std::shared_ptr<NAI::Goap::IAgent> CreateAgent(NPCTypes type, ANPCAIController* controller, INPCCharacter* character, std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem);

	private:
		std::shared_ptr<NAI::Goap::IAgent> CreateHuman(ANPCAIController* controller, INPCCharacter* character, std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const;
		std::shared_ptr<NAI::Goap::IAgent> CreateChicken(ANPCAIController* controller, INPCCharacter* character, std::shared_ptr<NAI::Goap::SensorySystem<NAI::Goap::IStimulus>> sensorySystem) const;

		AEventDispatcher* mEventDispatcher;
		std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
	};
}
