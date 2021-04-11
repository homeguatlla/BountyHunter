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
	float GetMaxWaitingTimeBetweenLocations() const override { return MaxWaitingTimeBetweenLocations; }
	float GetMinWaitingTimeBetweenLocations() const override { return MinWaitingTimeBetweenLocations; }

	/** Radius of exploration from Pawn Position */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float Radius;

	/** Max time in seconds before explore a new location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float MaxWaitingTimeBetweenLocations;

	/** Min time in seconds before explore a new location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Esplore Attributes")
	float MinWaitingTimeBetweenLocations;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	bool mIsExploring;
};
