#include <BountyHunter/Abilities/HealthAbility.h>
#include <BountyHunter/Abilities/Ability.h>
#include <BountyHunter/Abilities/DataAssets/DA_CharacterAbility.h>
#include <BountyHunter/Abilities/DataAssets/DA_HealthAbility.h>

#include <BountyHunter/Character/CharacterAttributes.h>
#include <BountyHunter/EventDispatcher.h>

namespace TLN
{
	HealthAbility::HealthAbility(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes) :
		AbilityBase(ability, abilityDA->GetManaCost(), abilityDA->GetCastingTime(), abilityDA->GetCooldownTime()),
		mCharacterAttributes { attributes },
		mAbilityDA { abilityDA }
	{
		auto healthAbilityDA = dynamic_cast<UDA_HealthAbility*>(abilityDA);
		mPercentage = healthAbilityDA->GetHealPercentage();
	}

	std::shared_ptr<IAbility> HealthAbility::Create(AAbility* ability, UDA_CharacterAbility* abilityDA, std::shared_ptr<TLN::CharacterAttributes> attributes)
	{
		return std::make_shared<HealthAbility>(ability, abilityDA, attributes);
	}

	void HealthAbility::DoStartCasting(const FVector& location)
	{
		if (mAAbility->IsValidLowLevel())
		{
			mAAbility->OnStartCasting(location);
		}
	}

	void HealthAbility::DoCastSpell()
	{
		IncrementLife();
		NotifyUpdateHealth();		

		if (mAAbility->IsValidLowLevel())
		{
			mAAbility->OnCast();
		}
	}

	UTexture2D* HealthAbility::GetIcon() const
	{ 
		return mAbilityDA->GetIcon(); 
	}

	void HealthAbility::NotifyUpdateHealth()
	{
		GetEventDispatcher()->OnUpdateHealth.Broadcast(mCharacterAttributes->GetHealth());
	}

	void HealthAbility::IncrementLife()
	{
		float newHealth = mCharacterAttributes->GetHealth() + mCharacterAttributes->GetHealth() * mPercentage;
		mCharacterAttributes->SetHealth(newHealth);
	}
}