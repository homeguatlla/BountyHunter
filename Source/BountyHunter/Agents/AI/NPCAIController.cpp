#include "NPCAIController.h"

#include <concrt.h>
#include <NAI/include/goap/IGoapPlanner.h>
#include <NAI/include/goap/goals/GoToGoal.h>
#include <NAI/include/goap/predicates/GoToPredicate.h>
#include <NAI/include/goap/planners/TreeGoapPlanner.h>

#include <BountyHunter/BountyHunterGameMode.h>
#include <BountyHunter/Agents/NPCAgentBuilder.h>
#include <BountyHunter/Agents/AI/NPCAgent.h>
#include <BountyHunter/utils/UtilsLibrary.h>



#include "BountyHunter/Agents/NPCAgentFactory.h"
#include "BountyHunter/Agents/NPCCharacter.h"
#include "GameFramework/Character.h"
#include "Runtime/AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"
#include "Engine/World.h"


void ANPCAIController::BeginPlay()
{
	Super::BeginPlay();
	
	CreateNavigationPlanner();

	auto npcCharacter = Cast<ANPCCharacter>(GetCharacter());
	check(npcCharacter != nullptr);
	
	CreateAgent(npcCharacter->GetNPCType());
}

void ANPCAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(mAgent != nullptr)
	{
		mAgent->Update(DeltaTime);
	}
}

void ANPCAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if(Result.IsSuccess())
	{
		//mNavigationPlanner->OnMoveCompleted();
	}
	else
	{
		//TODO movement interrupted or failed.
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

void ANPCAIController::AddNewPredicate(std::shared_ptr<NAI::Goap::IPredicate> predicate)
{
	assert(mAgent != nullptr);
	
	mAgent->OnNewPredicate(predicate);
}

void ANPCAIController::CreateNavigationPlanner()
{
	mNavigationPlanner = std::make_shared<NavigationPlanner>(GetWorld());
}

void ANPCAIController::CreateAgent(NPCTypes type)
{
	const auto world = GetWorld();
	if(world->IsValidLowLevel())
	{
		auto gameMode = world->GetAuthGameMode<ABountyHunterGameMode>();

		if (gameMode->IsValidLowLevel())
		{
			const auto eventDispatcher = gameMode->GetEventDispatcher();
			NPCAgentFactory factory(eventDispatcher, mNavigationPlanner);
			mAgent = factory.CreateAgent(type, this);

			mAgent->StartUp();
		}
	}
}