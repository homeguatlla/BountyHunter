#pragma once
#include <string>
#include <map>

namespace TLN
{
	namespace Chicken
	{
		enum class ChickenState
		{
			STATE_IDLE = 0,
            STATE_WALKING = 1,
            STATE_RUNNING = 2,
            STATE_JUMPING = 3,
            STATE_ON_AIR = 4,
			STATE_EAT = 5,
			STATE_EXPLORE = 6,
			STATE_ESCAPE = 7
        };
        
        static std::map<ChickenState, std::string> ChickenStateMap =
        {
        			{ ChickenState::STATE_IDLE, std::string("Idle") },
        			{ ChickenState::STATE_WALKING, std::string("Walking") },
					{ ChickenState::STATE_RUNNING, std::string("Running") },
					{ ChickenState::STATE_JUMPING, std::string("Jumping") },
					{ ChickenState::STATE_ON_AIR, std::string("OnAir") },
					{ ChickenState::STATE_EAT, std::string("Eating") },
					{ ChickenState::STATE_EXPLORE, std::string("Exploring") },
					{ ChickenState::STATE_ESCAPE, std::string("Escape") }
        };
	};
}
