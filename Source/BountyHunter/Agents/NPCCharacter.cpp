#include "NPCCharacter.h"

#include "Components/EatComponent.h"

float ANPCCharacter::GetMovementSpeed() const
{
	return GetVelocity().Size();
}

bool ANPCCharacter::IsEating() const
{
	const auto eatComponent = FindComponentByClass<UEatComponent>();
	check(eatComponent != nullptr && eatComponent->GetClass()->ImplementsInterface(UIEatComponent::StaticClass()));

	if(!eatComponent)
	{
		return false;
	}
	else
	{
		const auto eatInterface = TScriptInterface<IIEatComponent>(eatComponent);
		return eatInterface->IsEating();
	}
}
