// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "goap/sensory/IStimulus.h"
#include <memory>
#include "InteractiveComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UInteractiveComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UInteractiveComponent();

	virtual std::shared_ptr<NAI::Goap::IStimulus> CreateStimulus() const { return nullptr; }
	bool IsBeingUsed() const { return mIsBeingUsed; }
	void Use() { mIsBeingUsed = true; }
	void Drop() { mIsBeingUsed = false; }
	
private:
	bool mIsBeingUsed;
};
