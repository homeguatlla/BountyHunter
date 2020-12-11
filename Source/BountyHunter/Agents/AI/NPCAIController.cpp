#include "NPCAIController.h"
#include <NAI/include/goap/IGoapPlanner.h>
#include <NAI/include/goap/goals/GoToGoal.h>
#include <NAI/include/goap/predicates/GoToPredicate.h>
#include <NAI/include/goap/planners/TreeGoapPlanner.h>

#include <BountyHunter/BountyHunterGameMode.h>
#include <BountyHunter/Agents/AgentBuilder.h>
#include <BountyHunter/Agents/AI/NPCAgent.h>
#include <BountyHunter/utils/UtilsLibrary.h>

#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"


void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	
	CreateNavigationPlanner();
	CreateAgent();
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(mAgent != nullptr)
	{
		mAgent->Update(DeltaTime);
	}
}

FVector ANPCAIController::GetPosition() const
{
	ACharacter* character = GetCharacter();
	return character->GetActorLocation();
}

void ANPCAIController::MoveTo(float elapsedTime, const FVector& point)
{
	if(point != mLastPoint || mLastPoint == FVector::ZeroVector)
	{
		mLastPoint = point;
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, point);
	}
}

FString ANPCAIController::GetAgentName_Implementation() const
{
	return GetCharacter()->GetName();
}

FString ANPCAIController::GetAgentCurrentState_Implementation() const
{
	return utils::UtilsLibrary::ConvertToFString(NAI::Goap::AgentStateMap[mAgent->GetCurrentState()]);
}

void ANPCAIController::CreateNavigationPlanner()
{
	mNavigationPlanner = std::make_shared<NavigationPlanner>(GetWorld());
}

void ANPCAIController::CreateAgent()
{
	AgentBuilder builder;

	const auto goToGoal = std::make_shared<NAI::Goap::GoToGoal>(mNavigationPlanner);
	const auto predicate1 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "GeneralStore");
	const auto predicate2 = std::make_shared<NAI::Goap::GoToPredicate>("GoTo", "Saloon");
	const auto world = GetWorld();
	if(world->IsValidLowLevel())
	{
		auto gameMode = world->GetAuthGameMode<ABountyHunterGameMode>();

		if (gameMode->IsValidLowLevel())
		{
			const auto eventDispatcher = gameMode->GetEventDispatcher();
			mAgent = builder.AddGoapPlanner(std::make_shared<NAI::Goap::TreeGoapPlanner>())
				.AddController(this)
				.AddGoal(goToGoal)
				.AddPredicate(predicate1)
				.AddPredicate(predicate2)
				.AddEventDispatcher(eventDispatcher)
				.Build<NPCAgent>();

			mAgent->StartUp();
		}
	}
}