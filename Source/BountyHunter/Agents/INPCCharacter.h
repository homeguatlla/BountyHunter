#pragma once

namespace TLN
{
	class INPCCharacter
	{
	public:
		virtual float GetMovementSpeed() const = 0;
		virtual bool IsEating() const = 0;
	};
}