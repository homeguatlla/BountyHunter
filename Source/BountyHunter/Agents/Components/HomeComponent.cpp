#include "HomeComponent.h"
#include "BountyHunter/Agents/AI/Goals/GoToHomeGoal.h"
#include <memory>

#include "BountyHunter/Agents/AI/NPCAIController.h"

UHomeComponent::UHomeComponent() : mIsGoingHome{false}
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UHomeComponent::BeginPlay()
{
	Super::BeginPlay();
	auto controller = GetNPCAIController();
	
	controller->AddNewGoal(
		std::make_shared<GoToHomeGoal>(
			this,
			controller->GetNavigationPlanner(),
			100.0f));//1meter
}


