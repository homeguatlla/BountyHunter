#pragma once

class UWorld;

namespace TLN
{
	namespace Chicken
	{
		class ChickenContext
		{
		public:
			ChickenContext(
                UWorld* world);

			~ChickenContext() = default;

		private:
			UWorld* mWorld;
		};
	};
}