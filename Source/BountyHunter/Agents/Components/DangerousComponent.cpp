#include "DangerousComponent.h"

#include "BountyHunter/Stimulus/DangerStimulus.h"
#include "BountyHunter/utils/UtilsLibrary.h"

UDangerousComponent::UDangerousComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

std::shared_ptr<NAI::Goap::IStimulus> UDangerousComponent::CreateStimulus() const
{
	const auto location = GetOwner()->GetActorLocation();
	const int id = GetOwner()->GetUniqueID();
	return std::make_shared<DangerStimulus>(id, utils::UtilsLibrary::ConvertToVec3(location), GetOwner());
}
