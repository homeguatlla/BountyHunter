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

	void SetExplore(bool isExploring) override { mIsExploring = isExploring; }
	bool IsExploring() const override;
	float GetExplorationRadius() const override { return Radius; }
	float GetWaitingTimeBetweenLocations() const override { return WaitingTimeBetweenLocations; }

	/** Radius of exploration from Pawn Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float Radius;

	/** Time in seconds before explore a new location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float WaitingTimeBetweenLocations;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool mIsExploring;
};
