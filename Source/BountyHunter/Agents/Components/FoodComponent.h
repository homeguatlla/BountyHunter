// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "InteractableComponent.h"
#include "FoodComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UFoodComponent : public UInteractableComponent
{
private:
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFoodComponent();
	std::shared_ptr<NAI::Goap::IStimulus> CreateStimulus() const override;

	/** Amount of units of food */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Food Attributes")
	uint8 Amount;
};
