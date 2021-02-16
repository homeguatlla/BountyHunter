#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NPCAgentComponent.generated.h"


class ANPCAIController;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UNPCAgentComponent : public UActorComponent
{
private:
	GENERATED_BODY()

	public:
		UNPCAgentComponent();
		ANPCAIController* GetNPCAIController() const { return mNPCAIController; }

		void BeginPlay() override;

	private:
		void SaveNPCAIController();
		void SaveActorHeadLocation();
	
	ANPCAIController* mNPCAIController;
};
