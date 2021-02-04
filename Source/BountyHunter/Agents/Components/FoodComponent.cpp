
#include "FoodComponent.h"

#include "BountyHunter/Stimulus/FoodStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"


UFoodComponent::UFoodComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

std::shared_ptr<NAI::Goap::IStimulus> UFoodComponent::CreateStimulus() const
{
	const auto location = GetOwner()->GetActorLocation();
	return std::make_shared<FoodStimulus>(utils::UtilsLibrary::ConvertToVec3(location), Amount, GetOwner());
}