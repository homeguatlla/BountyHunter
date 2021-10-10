﻿#include "NPCCharacter.h"

#include "Components/EatComponent.h"
#include "Components/EscapeComponent.h"
#include "Components/ExploreComponent.h"

float ANPCCharacter::GetMovementSpeed() const
{
	return GetVelocity().Size();
}

bool ANPCCharacter::IsEating() const
{
	const auto eatComponent = GetComponent<UEatComponent, IIEatComponent, UIEatComponent>();
	if(eatComponent)
	{
		return eatComponent->IsEating();
	}

	return false;
}


bool ANPCCharacter::IsExploring() const
{
	const auto exploreComponent = GetComponent<UExploreComponent, IIExploreComponent, UIExploreComponent>();
	if(exploreComponent)
	{
		return exploreComponent->IsExploring();
	}

	return false;
}

bool ANPCCharacter::IsEscaping() const
{
	const auto escapeComponent = GetComponent<UEscapeComponent, IIEscapeComponent, UIEscapeComponent>();
	if(escapeComponent)
	{
		return escapeComponent->IsEscaping();
	}

	return false;
}
