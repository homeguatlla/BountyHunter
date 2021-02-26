#pragma once

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
        };
	};
}