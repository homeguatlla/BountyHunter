#pragma once
#include "CoreMinimal.h"
#include <BountyHunter/Character/InputHandler.h>
#include <BountyHunter/Abilities/IAbility.h>
#include <memory>
#include <vector>
#include <map>

namespace TLN
{
	class AbilitiesToolChest
	{
		std::vector<std::shared_ptr<IAbility>> mAbilities;
		std::map<InputAction, int> mAbilitiesInToolBelt;

		public:
			AbilitiesToolChest() = default;
			~AbilitiesToolChest() = default;

			int AddAbility(std::shared_ptr<IAbility> ability);
			void BindAbilityToToolBelt(InputAction action, int index);
			bool CanCast(InputAction action, int availableMana) const;
			bool IsReadyToCast() const;
			std::shared_ptr<IAbility> GetAbility(InputAction action);
			const std::shared_ptr<IAbility> GetAbility(InputAction action) const;
	};
};