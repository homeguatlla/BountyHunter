// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NPCAgentComponent.h"
#include "Components/ActorComponent.h"
#include <goap/sensory/BaseSensor.h>

#include "VisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UVisionComponent : public UNPCAgentComponent//, public NAI::Goap::BaseSensor
{
	GENERATED_BODY()

public:
	UVisionComponent();

	/** Radius of the sphere volume to propagate from head to length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	float Radius;
	
	/** Length of view */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	int LengthOfView;

	/** If true, draw debug lines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	bool IsDebug;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:
	void DrawDebugLines(const FVector& head, const FVector& pointOfSight, const FRotator& rotation,
	                    const FVector& forward);
};
