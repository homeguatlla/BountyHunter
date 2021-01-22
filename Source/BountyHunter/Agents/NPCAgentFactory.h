#pragma once
#include <memory>

#include "NPCTypes.h"

class ANPCAIController;
class AEventDispatcher;

namespace NAI {
	namespace Goap {
		class IAgent;
	}
	namespace Navigation {
		class INavigationPlanner;
	}
}

class NPCAgentFactory
{
public:
	NPCAgentFactory(AEventDispatcher* eventDispatcher,std::shared_ptr<NAI::Navigation::INavigationPlanner> planner);
	virtual ~NPCAgentFactory() = default;

	std::shared_ptr<NAI::Goap::IAgent> CreateAgent(NPCTypes type, ANPCAIController* controller);

private:
	AEventDispatcher* mEventDispatcher;
	std::shared_ptr<NAI::Navigation::INavigationPlanner> mNavigationPlanner;
};
