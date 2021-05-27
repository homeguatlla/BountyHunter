// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "goap/sensory/IStimulus.h"
#include <memory>
#include "DangerousComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UDangerousComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDangerousComponent();

	virtual std::shared_ptr<NAI::Goap::IStimulus> CreateStimulus() const;
};
