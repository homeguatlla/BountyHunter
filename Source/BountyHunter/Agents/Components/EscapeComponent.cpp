#include "EscapeComponent.h"

#include <memory>

#include "BountyHunter/Agents/AI/NPCAIController.h"
#include "BountyHunter/Agents/AI/Goals/EscapeGoal.h"

UEscapeComponent::UEscapeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
}

void UEscapeComponent::BeginPlay()
{
	Super::BeginPlay();

	auto controller = GetNPCAIController();
	controller->AddNewGoal(std::make_shared<EscapeGoal>(this));
}

void UEscapeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}
