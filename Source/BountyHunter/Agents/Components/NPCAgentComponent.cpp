
#include "NPCAgentComponent.h"
#include "BountyHunter/Agents/AI/IAgentAIController.h"
#include "BountyHunter/Agents/AI/NPCAIController.h"
#include "GameFramework/Actor.h"

UNPCAgentComponent::UNPCAgentComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UNPCAgentComponent::BeginPlay()
{
	SaveNPCAIController();
}

void UNPCAgentComponent::SaveNPCAIController()
{
	const auto actor = GetOwner();
	
	const auto controller = actor->GetInstigatorController<IAgentAIController>();

	checkf(controller != nullptr, TEXT("[UNPCAgentComponent::SaveNPCAIController] AIAgentController is null"));

	mNPCAIController = Cast<ANPCAIController>(controller);
}

