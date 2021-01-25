// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UEatComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEatComponent();

	bool HasHungry() const { return mHasHungry; }
	bool IsEating() const { return mIsEating; }
	void Eat(unsigned int amount);

	/** Time spends to eat one amount of food, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Eat Attributes")
	float EatingSpeed;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	unsigned int mAmount;
	bool mIsEating;
	bool mHasHungry;
};
