#pragma once

class UWorld;

namespace TLN
{
	class INPCCharacter;

	namespace Chicken
	{
		class ChickenContext
		{
		public:
			ChickenContext(
                UWorld* world,
                INPCCharacter* character);

			~ChickenContext() = default;

			INPCCharacter* GetCharacter() const { return mCharacter; }
		private:
			UWorld* mWorld;
			INPCCharacter* mCharacter;
		};
	};
}