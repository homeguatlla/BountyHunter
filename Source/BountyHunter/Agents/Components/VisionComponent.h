// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "NPCAgentComponent.h"
#include "Components/ActorComponent.h"
#include <goap/sensory/BaseSensor.h>

#include "VisionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BOUNTYHUNTER_API UVisionComponent : public UNPCAgentComponent
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

	/** Time spends to eat one amount of food, in seconds */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	FName HeadBoneName;
	
	/** If true, draw debug lines */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Vision Attributes")
	bool IsDebug;

	void BeginPlay() override;
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	

private:
	FVector GetActorHeadLocation() const { return mActorHeadLocation; }
	void SaveActorHeadLocation();
	void DrawDebugLines(const FVector& head, const FVector& pointOfSight, const FRotator& rotation,
	                    const FVector& forward) const;

	std::shared_ptr<NAI::Goap::BaseSensor> mSensor;
	FVector mActorHeadLocation;
};
