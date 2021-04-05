#pragma once
#include "InputHandler.h"
#include "fsm/states/CharacterStates.h"
/*#include "IBHPlayerController.generated.h"

UINTERFACE()
class UBHPlayerController : public UInterface
{
	GENERATED_BODY()
};

class IBHPlayerController
{
	GENERATED_BODY()
public:
	//UFUNCTION()
	virtual TLN::CharacterState GetCurrentStateID(int machineId) const = 0;
	virtual bool IsActionPressed(TLN::InputAction action) const = 0;
};
*/

namespace TLN
{
	class IBHPlayerController
	{
	public:
		virtual CharacterState GetCurrentStateID(int machineId) const = 0;
		virtual bool IsActionPressed(InputAction action) const = 0;

		void Empty() {}
	};
}
