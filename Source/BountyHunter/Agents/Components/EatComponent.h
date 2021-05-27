// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "IEatComponent.h"
#include "BountyHunter/Agents/Components/NPCAgentComponent.h"
#include "EatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UEatComponent : public UNPCAgentComponent, public IIEatComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEatComponent();

	bool HasHungry() const override { return !IsEating() && AccumulatedTimeToStartHavingHungry <= MinAccumulatedTimeToBeFull; }
	bool IsEating() const override { return mEatingTime > 0.0f; }	
	void Eat(uint8 amount) override;
	float GetMinDistanceToEat() const override { return MinDistanceToEat; }
	void Cancel() override;
	
	/** Time spends to eat one amount of food, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float EatingSpeed;
	
	/** Time in seconds the agent can stay without eat per amount eaten */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float TimeWithoutHungryPerAmountEaten;

	/** Time in seconds the agent can stay without eat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float AccumulatedTimeToStartHavingHungry;

	/** Time in seconds the agent can stay without eat */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float MinAccumulatedTimeToBeFull;

	/** Min distance to start eating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float MinDistanceToEat;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	void UpdateEating(float elapsedTime);
	void UpdateHungry(float elapsedTime);
	void AddHungryPredicateToAgent() const;

	unsigned int mAmount;
	float mEatingTime;
};
