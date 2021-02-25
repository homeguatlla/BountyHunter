#include "NPCCharacter.h"

float ANPCCharacter::GetMovementSpeed() const
{
	return GetVelocity().Size();
}
