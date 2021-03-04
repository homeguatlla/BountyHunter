// Fill out your copyright notice in the Description page of Project Settings.
#include "ExploreComponent.h"
#include "BountyHunter/Agents/AI/Goals/ExploreGoal.h"
#include <memory>

#include "BountyHunter/Agents/AI/NPCAIController.h"

// Sets default values for this component's properties
UExploreComponent::UExploreComponent() : mIsExploring{false}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void UExploreComponent::BeginPlay()
{
	Super::BeginPlay();
	auto controller = GetNPCAIController();
	
	controller->AddNewGoal(
		std::make_shared<ExploreGoal>(
			this,
			controller->GetNavigationPlanner(),
			100.0f));//1meter
}

bool UExploreComponent::IsExploring() const
{
	return mIsExploring;
}


