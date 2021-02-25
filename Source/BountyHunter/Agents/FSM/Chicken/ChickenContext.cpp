
#include "ChickenContext.h"

namespace TLN
{
	namespace Chicken
	{
		ChickenContext::ChickenContext(
            UWorld* world,
            INPCCharacter* character) :
            mWorld {world},
			mCharacter{character}
		{
		}
	}
}
