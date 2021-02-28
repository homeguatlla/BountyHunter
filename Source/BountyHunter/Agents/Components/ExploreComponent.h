// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IExploreComponent.h"
#include "NPCAgentComponent.h"
#include "ExploreComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UExploreComponent : public UNPCAgentComponent, public IIExploreComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UExploreComponent();
	
	bool IsExploring() const override;
	float GetExplorationRadius() const override { return Radius; }

	/** Time in seconds the agent can stay without eat per amount eaten */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float Radius;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool mIsExploring;
};
